#ifndef __RESOURCE_MESH__
#define __RESOURCE_MESH__

#include "Resource.h"
#include "Globals.h"
#include "MathGeoLib/include/Geometry/AABB.h"

struct Vertex {
	float position[3];
	float normal[3];
	unsigned char color[4];
	float texCoord[2];
};

class ResourceMesh : public Resource
{
public:

	ResourceMesh();
	~ResourceMesh();

	void CreateAABB();

	void LoadOnMemory();
	void FreeMemory();

private:
	void CreateVBO();
	void CreateEBO();
	void CreateVAO();

public:

	Vertex* Vertices = nullptr;
	uint VerticesSize = 0;

	uint* Indices = nullptr;
	uint IndicesSize = 0;

	uint VBO = 0;	// Vertex Buffer Object
	uint EBO = 0;	// Element/Index Buffer Object

	uint VAO = 0;	// Vertex Array Object

	AABB aabb;
};

#endif // __RESOURCE_MESH__

