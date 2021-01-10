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
			variable() { //These must be initialized
				Uint = 0;
				Ufloat = 0.f;
				Ufloat2 = { 0.f, 0.f };
				Ufloat3 = { 0.f, 0.f, 0.f };
				Ufloat4 = { 0.f, 0.f, 0.f, 0.f };
				Ubool = true;
			}
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
	void Use() const;
	void ReloadAndCompileShader();
	void FillUniform(Uniform& uniform, const char* name, const uint type) const;

	/* Program variabless */
	uint shaderID = 0;
	std::string ShaderCode;
	std::string VertexCode;
	std::string FragmentCode;

private:
	uint vertexID = 0;
	uint fragmentID = 0;

	bool LoadFromFile();

	inline bool CreateVertexShader(uint& vID);
	bool CreateVertexShader();
	bool CreateFragmentShader(uint& fID);
	inline bool CreateFragmentShader();
	bool CreateShaderProgram();
	void DeleteShaderProgram();
};

#endif //__RESOURCE_SHADER_H__