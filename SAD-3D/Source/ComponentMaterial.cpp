#include "ComponentMaterial.h"

// Resources
#include "ResourceMaterial.h"
#include "ResourceTexture.h"

#include "mmgr/mmgr.h"

ComponentMaterial::ComponentMaterial(Component::ComponentType type) : Component(type)
{
	// MYTODO: We are not setting any container GO, should point to future root?
}

ComponentMaterial::~ComponentMaterial()
{	
	FreeTexture();
}

void ComponentMaterial::FreeTexture()
{
	resource_material->resource_diffuse->Free();
}



