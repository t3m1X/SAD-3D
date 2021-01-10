#ifndef __RESOURCE_MATERIAL_H__
#define __RESOURCE_MATERIAL_H__

#include "Resource.h"
#include "Globals.h"
#include <vector>
#include "ResourceShader.h"

class ResourceTexture;

class ResourceMaterial : public Resource
{
public:
	ResourceMaterial();
	~ResourceMaterial();

	void UpdateUniforms();

public:
	ResourceTexture* resource_diffuse = nullptr;
	ResourceShader* shader = nullptr;
	std::vector<ResourceShader::Uniform*> uniforms;

};

#endif //__RESOURCE_MATERIAL_H__