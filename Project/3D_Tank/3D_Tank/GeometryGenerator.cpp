#include "GeometryGenerator.h"

std::map<GeometryGenerator::MeshType, GeometryGenerator::Mesh> GeometryGenerator::mMeshes;

void GeometryGenerator::getMesh(MeshType type, Mesh& mesh)
{
	if (mMeshes[type].vertices.size() == 0 || mMeshes[type].indices.size() == 0)
	{
		switch (type)
		{
		case GeometryGenerator::BOX:
			createBox();
			break;
		case GeometryGenerator::Sphere:
			createSphere();
			break;
		case GeometryGenerator::Plane:
			createPlane();
			break;
		}
	}

	mesh = mMeshes[type];
}

void GeometryGenerator::createBox()
{
	const std::vector<Vertex> vertices =
	{
		{ -1.0f,-1.0f,-1.0f },
		{ 1.0f,-1.0f,-1.0f },
		{ -1.0f,1.0f,-1.0f },
		{ 1.0f,1.0f,-1.0f },
		{ -1.0f,-1.0f,1.0f },
		{ 1.0f,-1.0f,1.0f },
		{ -1.0f,1.0f,1.0f },
		{ 1.0f,1.0f,1.0f },
	};

	const std::vector<UINT> indices =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};

	mMeshes[MeshType::BOX].vertices = vertices;
	mMeshes[MeshType::BOX].indices = indices;
}

void GeometryGenerator::createSphere()
{
}

void GeometryGenerator::createPlane()
{
}