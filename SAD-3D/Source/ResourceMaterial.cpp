#include "ResourceMaterial.h"

#include "Application.h"
#include "ModuleRenderer3D.h"

#include "ResourceTexture.h"
#include "OpenGL.h"
#include "mmgr/mmgr.h"

ResourceMaterial::ResourceMaterial() : Resource(Resource::ResourceType::MATERIAL)
{
	shader = App->renderer3D->defaultShader;
	shader->Load();

	shader->GetAllUniforms(uniforms);
}

ResourceMaterial::~ResourceMaterial()
{
	if (shader)
		shader->Free();

	for (uint i = 0; i < uniforms.size(); ++i)
		delete uniforms[i];

	uniforms.clear();
}

void ResourceMaterial::UpdateUniforms() {
	glUseProgram(shader->shaderID);

	for (uint i = 0; i < uniforms.size(); ++i) {

		switch (uniforms[i]->type) {
		case GL_INT:
			glUniform1i(uniforms[i]->location, uniforms[i]->value.Uint);
			break;

		case GL_FLOAT:
			glUniform1f(uniforms[i]->location, uniforms[i]->value.Ufloat);
			break;

		case GL_FLOAT_VEC2:
			glUniform2f(uniforms[i]->location, uniforms[i]->value.Ufloat2.x, uniforms[i]->value.Ufloat2.y);
			break;

		case GL_FLOAT_VEC3:
			glUniform3f(uniforms[i]->location, uniforms[i]->value.Ufloat3.x, uniforms[i]->value.Ufloat3.y, uniforms[i]->value.Ufloat3.z);
			break;

		case GL_FLOAT_VEC4:
			glUniform4f(uniforms[i]->location, uniforms[i]->value.Ufloat4.x, uniforms[i]->value.Ufloat4.y, uniforms[i]->value.Ufloat4.z, uniforms[i]->value.Ufloat4.w);
			break;

		case GL_INT_VEC2:
			glUniform2i(uniforms[i]->location, uniforms[i]->value.Ufloat2.x, uniforms[i]->value.Ufloat2.y);
			break;

		case GL_INT_VEC3:
			glUniform3i(uniforms[i]->location, uniforms[i]->value.Ufloat3.x, uniforms[i]->value.Ufloat3.y, uniforms[i]->value.Ufloat3.z);
			break;

		case GL_INT_VEC4:
			glUniform4i(uniforms[i]->location, uniforms[i]->value.Ufloat4.x, uniforms[i]->value.Ufloat4.y, uniforms[i]->value.Ufloat4.z, uniforms[i]->value.Ufloat4.w);
			break;
		
		case GL_BOOL:
			glUniform1i(uniforms[i]->location, uniforms[i]->value.Ubool);
			break;
		}
	}

	glUseProgram(App->renderer3D->defaultShader->shaderID);
}
