#ifndef __COMPONENT_MATERIAL_H__
#define __COMPONENT_MATERIAL_H__

#include "Component.h"

class ResourceMaterial;
class ComponentMaterial : public Component
{
public:

	ComponentMaterial(Component::ComponentType type);
	virtual ~ComponentMaterial();

	void FreeTexture();
public:

	ResourceMaterial * resource_material = nullptr;
};

#endif