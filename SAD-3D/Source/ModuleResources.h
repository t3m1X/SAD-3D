#ifndef __MODULE_RESOURCES_H__
#define __MODULE_RESOURCES_H__

#include "Module.h"
#include "Globals.h"
#include "Resource.h"

struct ResourceMeta
{
	uint Date = 0;
	uint UID = 0;
};

class ModuleResources : public Module
{
public:

	ModuleResources(bool start_enabled = true);
	~ModuleResources();

	bool Init(json file);
	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void CreateMetaFromUID(uint UID, const char* filename);

	bool IsFileImported(const char* file);
	Resource* GetResource(const char* original_file);
	Resource::ResourceType GetResourceTypeFromPath(const char* path);
	uint GetUIDFromMeta(const char* file);
	uint GetModDateFromMeta(const char* file);

	void DeleteResource(uint UID);

	std::map<std::string, Resource*> GetResourceNamesByType(const Resource::ResourceType type);

	Resource* CreateResource(Resource::ResourceType type, uint UID = 0);

private:
	// --- Resources in memory ---
	std::map<uint, Resource*> resources;

	// --- Resources in library ---
	std::map<uint, ResourceMeta> LoadedResources;
};

#endif