#include "ResourceShader.h"
#include "Application.h"
#include "ModuleFileSystem.h"

#include "OpenGL.h"

void ResourceShader::LoadOnMemory() {
	if (LoadFromFile()) {
		DeleteShaderProgram();

		/* Separate vertex and fragment shaders */

		std::string vtag = "#version";
		std::string ftag = "#define FRAGMENT_SHADER";

		uint version_location = ShaderCode.find(vtag);
		uint version_end_location = ShaderCode.find_first_of('\n', version_location);
		uint fragment_location = ShaderCode.find(ftag);

		vShaderCode = ShaderCode.substr(0, fragment_location - 1);
		fShaderCode = ShaderCode.substr(version_location, version_end_location);
		fShaderCode += ShaderCode.substr(fragment_location, ShaderCode.size());

		/* Compile shaders */
		char error_log[512];

		if (!CreateVertexShader()) {
			glGetShaderInfoLog(vertexID, 512, NULL, error_log);
			CONSOLE_LOG("|[Error]: Vertex Shader failed to compile - %s", error_log);
		}

		if (!CreateFragmentShader()) {
			glGetShaderInfoLog(fragmentID, 512, NULL, error_log);
			CONSOLE_LOG("|[Error]: Fragment Shader failed to compile - %s", error_log);
		}

		if (!CreateShaderProgram()) {
			glGetShaderInfoLog(shaderID, 512, NULL, error_log);
			CONSOLE_LOG("|[Error]: Shader failed to link - %s", error_log);
		}

		// We no longer need fragment and vertex shaders
		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
	}
}

void ResourceShader::FreeMemory() {
	DeleteShaderProgram();
}

void ResourceShader::SetUniformByName(const char* name, Uniform::variable& udata, const uint& type) const {
	switch (type) {
	case GL_INT:
		glUniform1i(glGetUniformLocation(shaderID, name), udata.Uint);
		break;

	case GL_FLOAT:
		glUniform1f(glGetUniformLocation(shaderID, name), udata.Ufloat);
		break;

	case GL_FLOAT_VEC2:
		glUniform2f(glGetUniformLocation(shaderID, name), udata.Ufloat2.x, udata.Ufloat2.y);
		break;

	case GL_FLOAT_VEC3:
		glUniform3f(glGetUniformLocation(shaderID, name), udata.Ufloat3.x, udata.Ufloat3.y, udata.Ufloat3.z);
		break;

	case GL_FLOAT_VEC4:
		glUniform4f(glGetUniformLocation(shaderID, name), udata.Ufloat4.x, udata.Ufloat4.y, udata.Ufloat4.z, udata.Ufloat4.w);
		break;

	case GL_BOOL:
		glUniform1i(glGetUniformLocation(shaderID, name), udata.Ubool);
		break;

	default:
		break;
	}
}

void ResourceShader::SetUniform(const Uniform& uniform) {
	switch (uniform.type) {
	case GL_INT:
		glUniform1i(uniform.location, uniform.value.Uint);
		break;

	case GL_FLOAT:
		glUniform1f(uniform.location, uniform.value.Ufloat);
		break;

	case GL_FLOAT_VEC2:
		glUniform2f(uniform.location, uniform.value.Ufloat2.x, uniform.value.Ufloat2.y);
		break;

	case GL_FLOAT_VEC3:
		glUniform3f(uniform.location, uniform.value.Ufloat3.x, uniform.value.Ufloat3.y, uniform.value.Ufloat3.z);
		break;

	case GL_FLOAT_VEC4:
		glUniform4f(uniform.location, uniform.value.Ufloat4.x, uniform.value.Ufloat4.y, uniform.value.Ufloat4.z, uniform.value.Ufloat4.w);
		break;

	case GL_BOOL:
		glUniform1i(uniform.location, uniform.value.Ubool);
		break;

	default:
		break;
	}

}

void ResourceShader::GetAllUniforms(std::vector<Uniform*>& uniforms) const {
	std::vector<Uniform*> my_uniforms;

	glUseProgram(shaderID);

	int u_count;
	glGetProgramiv(shaderID, GL_ACTIVE_UNIFORMS, &u_count);

	const int kTotalChars = 128;
	char name[kTotalChars];
	uint type;
	GLint size;

	for (int i = 0; i < u_count; ++i) {
		glGetActiveUniform(shaderID, i, kTotalChars, nullptr, &size, &type, name);
		size_t sad_var = std::string(name).find("SAD_");

		if (sad_var != std::string::npos && sad_var == 0)
			continue; // Engine reserved variables, not displayable.

		Uniform* uniform = nullptr;
		
		switch (type) {
			//mTODO: maybe there is a better way to do this?
		case GL_FLOAT:
		case GL_FLOAT_VEC2:
		case GL_FLOAT_VEC3:
		case GL_FLOAT_VEC4:
		case GL_INT:
		case GL_INT_VEC2:
		case GL_INT_VEC3:
		case GL_INT_VEC4:
		case GL_BOOL:
			uniform = new Uniform();
			uniform->name = name;
			uniform->location = glGetUniformLocation(shaderID, name);
			uniform->type = type;
			break;
			
		default:
			//Unsupported 
			continue;
		}

		// We preserve whatever value we have
		for (auto iterator = uniforms.begin(); iterator != uniforms.end(); ++iterator) {
			if ((*iterator)->name == uniform->name && (*iterator)->type == uniform->type) {
				uniform->value = (*iterator)->value;
				delete (*iterator);
				uniforms.erase(iterator);

				break;
			}
		}

		my_uniforms.push_back(uniform);
	}

	for (uint i = 0; i < uniforms.size(); ++i)
		delete uniforms[i];
	uniforms.clear();

	uniforms = my_uniforms;
}

inline void ResourceShader::Use() const {
	glUseProgram(shaderID);
}

void ResourceShader::ReloadAndCompileShader() {
	uint newVertexID, newFragmentID = 0;

	/* Compile new vertex shaders */
	const uint kErrorSize = 512;
	char error_log[kErrorSize];
	bool failed_compilation = false;

	if (!CreateVertexShader(newVertexID)) {
		glGetShaderInfoLog(newVertexID, kErrorSize, NULL, error_log);
		CONSOLE_LOG("|[Error]: Vertex Shader failed to compile - %s", error_log);
		failed_compilation = true;
	}

	if (!CreateFragmentShader(newFragmentID)) {
		glGetShaderInfoLog(newFragmentID, kErrorSize, NULL, error_log);
		CONSOLE_LOG("|[Error]: Fragment Shader failed to compile - %s", error_log);
		failed_compilation = true;
	}

	if (!failed_compilation) {
		/* Delete the old and attach the new */
		glDetachShader(shaderID, vertexID);
		glDetachShader(shaderID, fragmentID);

		GLint success = 0;
		glAttachShader(shaderID, newVertexID);
		glAttachShader(shaderID, newFragmentID);
		glLinkProgram(shaderID);
		glGetProgramiv(shaderID, GL_LINK_STATUS, &success);

		if (success) {
			/* On sucess we delete the old shader vertex and fragment and update the IDs */
			glDeleteShader(vertexID);
			glDeleteShader(shaderID);
			vertexID = newVertexID;
			fragmentID = newFragmentID;
		}
		else {
			/* On failure we detach and delete the new, reattach the old */

			glGetShaderInfoLog(shaderID, kErrorSize, NULL, error_log);
			CONSOLE_LOG("|[Error]: Shader failed to link - %s", error_log);

			glDetachShader(shaderID, newVertexID);
			glDetachShader(shaderID, newFragmentID);
			glDeleteShader(newVertexID);
			glDeleteShader(newFragmentID);

			glAttachShader(shaderID, newVertexID);
			glAttachShader(shaderID, newFragmentID);
		}
	}
	else {
		glDeleteShader(newVertexID);
		glDeleteShader(newFragmentID);
	}
}

void ResourceShader::FillUniform(Uniform& uniform, const char* name, const uint type) const {
	uniform.name = name;
	uniform.location = glGetUniformLocation(shaderID, name);
	uniform.type = type;
}

bool ResourceShader::LoadFromFile() {
	char* buffer;
	bool ret = static_cast<bool>(App->fs->Load(original_file.c_str(), &buffer));

	ShaderCode = buffer;
	delete[] buffer;

	return ret;
}


