#ifndef __RESOURCE_SHADER_H__
#define __RESOURCE_SHADER_H__

#include "Resource.h"
#include "Math.h"
#include <string>
#include <vector>

class ResourceShader : public Resource {
public:
	// Shader uniforms
	struct Uniform {
		union variable {
			int Uint;
			float Ufloat;
			float2 Ufloat2;
			float3 Ufloat3;
			float4 Ufloat4;
			char Ubool;
		};

		Uniform() {} //Apparently this is needed?

		std::string name;
		uint location = 0;
		uint type = 0;
		variable value;
	};

	ResourceShader();
	~ResourceShader();

	void LoadOnMemory() override;
	void FreeMemory() override;

	/* Setters */
	void SetUniformByName(const char* name, Uniform::variable& udata, const uint& type) const;
	void SetUniform(const Uniform& uniform);

	/* Getters */
	void GetAllUniforms(std::vector<Uniform*>& uniforms) const;

	/* Utilities */
	void inline Use() const;
	void ReloadAndCompileShader();
	void FillUniform(Uniform& uniform, const char* name, const uint type) const;

	/* Program variabless */
	uint shaderID = 0;
	std::string ShaderCode;
	std::string vShaderCode;
	std::string fShaderCode;

private:
	uint vertexID = 0;
	uint fragmentID = 0;

	bool LoadFromFile();

	bool CreateVertexShader(uint vertexID);
	bool CreateVertexShader();
	bool CreateFragmentShader(uint fragmentID);
	bool CreateFragmentShader();
	bool CreateShaderProgram();
	void DeleteShaderProgram();
};

#endif //__RESOURCE_SHADER_H__