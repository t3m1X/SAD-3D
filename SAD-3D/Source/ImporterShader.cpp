#include "ImporterShader.h"

#include "Application.h"
#include "ModuleResources.h"
#include "ModuleFileSystem.h"

#include "ResourceShader.h"

ImporterShader::ImporterShader() {}
ImporterShader::~ImporterShader() {}

bool ImporterShader::Import(const ImportData& IData) const {
	ImportShaderData mdata = (ImportShaderData&)IData;
	bool ret = true;

	if (!mdata.path)
		return false;

	ResourceShader* new_shader = nullptr;

	if (App->resources->IsFileImported(mdata.path)) {

		uint UID = App->resources->GetUIDFromMeta(mdata.path);
		new_shader = (ResourceShader*)App->resources->CreateResource(Resource::ResourceType::SHADER, UID);
		new_shader->SetOriginalFilename(mdata.path);
		new_shader->Load();

		if (new_shader->shaderID) {
			// Extracting file name from path
			std::string name = mdata.path;
			uint pivot = name.find_last_of('/');
			name = name.substr(pivot + 1, name.size());
			pivot = name.find_last_of('.');
			new_shader->SetName(name.substr(0, pivot).c_str());
		}
		else {
			App->resources->DeleteResource(new_shader->GetUID());
			ret = false;
		}
		
	}
	else {
		new_shader = (ResourceShader*)App->resources->CreateResource(Resource::ResourceType::SHADER);
		new_shader->SetOriginalFilename(mdata.path);
		new_shader->Load();

		if (new_shader->shaderID) {
			// Extracting file name from path
			std::string name = mdata.path;
			uint pivot = name.find_last_of('/');
			name = name.substr(pivot + 1, name.size());
			pivot = name.find_last_of('.');
			new_shader->SetName(name.substr(0, pivot).c_str());

			App->resources->CreateMetaFromUID(new_shader->GetUID(), mdata.path);
		}
		else {
			App->resources->DeleteResource(new_shader->GetUID());
			ret = false;
		}
	}

	return ret;
}

void ImporterShader::Save(ResourceShader* shader) const {
	std::string original_file = shader->GetOriginalFile();
	std::string code = shader->ShaderCode;
	App->fs->Save(original_file.c_str(), code.c_str(), code.size() * sizeof(char));
}

