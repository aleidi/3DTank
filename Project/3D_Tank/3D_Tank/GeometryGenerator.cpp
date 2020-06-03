#include "GeometryGenerator.h"
#include "FileManager.h"

std::map<GeometryGenerator::MeshType, GeometryGenerator::Mesh> GeometryGenerator::mMeshes;
std::map<std::string, GeometryGenerator::Mesh> GeometryGenerator::mModels;

void GeometryGenerator::getCube(Mesh & mesh)
{
	if (mMeshes[MeshType::Cube].vertices.size() == 0 || mMeshes[MeshType::Cube].indices.size() == 0)
	{
		createCube();
	}
	mesh = mMeshes[MeshType::Cube];
}

void GeometryGenerator::getSphere(Mesh & mesh)
{
	if (mMeshes[MeshType::Sphere].vertices.size() == 0 || mMeshes[MeshType::Sphere].indices.size() == 0)
	{
		createSphere();
	}
	mesh = mMeshes[MeshType::Sphere];
}

void GeometryGenerator::getPlane(Mesh & mesh)
{
	if (mMeshes[MeshType::Plane].vertices.size() == 0 || mMeshes[MeshType::Plane].indices.size() == 0)
	{
		createPlane();
	}
	mesh = mMeshes[MeshType::Plane];
}

void GeometryGenerator::getModel(Mesh & mesh, const std::string & name)
{
	if (mModels[name].vertices.size() == 0 || mModels[name].indices.size() == 0)
	{
		createModel(name);
	}
	mesh = mModels[name];
}

void GeometryGenerator::createCube()
{
	std::vector<Vertex> vertices =
	{
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },

		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
	};

	const std::vector<UINT> indices =
	{
		3,1,0,
		2,1,3,

		6,4,5,
		7,4,6,

		11,9,8,
		10,9,11,

		14,12,13,
		15,12,14,

		19,17,16,
		18,17,19,

		22,20,21,
		23,20,22
	};

	mMeshes[MeshType::Cube].vertices = vertices;
	mMeshes[MeshType::Cube].indices = indices;
}

void GeometryGenerator::createSphere()
{
	Mesh meshData;
	UINT stackCount = 20;
	UINT sliceCount = 20;
	float radius = 1.0f;
	//
	// Compute the vertices stating at the top pole and moving down the stacks.
	//

	// Poles: note that there will be texture coordinate distortion as there is
	// not a unique point on the texture map to assign to the pole when mapping
	// a rectangular texture onto a sphere.
	Vertex topVertex{ XMFLOAT3(0.0f, +radius, 0.0f), XMFLOAT2(0.0f, 0.0f) };
	Vertex bottomVertex{ XMFLOAT3(0.0f, -radius, 0.0f),XMFLOAT2(0.0f, 1.0f) };

	meshData.vertices.push_back(topVertex);

	float phiStep = XM_PI / stackCount;
	float thetaStep = 2.0f*XM_PI / sliceCount;

	// Compute vertices for each stack ring (do not count the poles as rings).
	for (UINT i = 1; i <= stackCount - 1; ++i)
	{
		float phi = i * phiStep;

		// Vertices of ring.
		for (UINT j = 0; j <= sliceCount; ++j)
		{
			float theta = j * thetaStep;

			Vertex v;

			// spherical to cartesian
			v.Position.x = radius * sinf(phi)*cosf(theta);
			v.Position.y = radius * cosf(phi);
			v.Position.z = radius * sinf(phi)*sinf(theta);

			//// Partial derivative of P with respect to theta
			//v.TangentU.x = -radius * sinf(phi)*sinf(theta);
			//v.TangentU.y = 0.0f;
			//v.TangentU.z = +radius * sinf(phi)*cosf(theta);

			//XMVECTOR T = XMLoadFloat3(&v.TangentU);
			//XMStoreFloat3(&v.TangentU, XMVector3Normalize(T));

			//XMVECTOR p = XMLoadFloat3(&v.Pos);
			//XMStoreFloat3(&v.Normal, XMVector3Normalize(p));

			v.Texcoord.x = theta / XM_2PI;
			v.Texcoord.y = phi / XM_PI;

			meshData.vertices.push_back(v);
		}
	}

	meshData.vertices.push_back(bottomVertex);

	//
	// Compute indices for top stack.  The top stack was written first to the vertex buffer
	// and connects the top pole to the first ring.
	//

	for (UINT i = 1; i <= sliceCount; ++i)
	{
		meshData.indices.push_back(0);
		meshData.indices.push_back(i + 1);
		meshData.indices.push_back(i);
	}

	//
	// Compute indices for inner stacks (not connected to poles).
	//

	// Offset the indices to the index of the first vertex in the first ring.
	// This is just skipping the top pole vertex.
	UINT baseIndex = 1;
	UINT ringVertexCount = sliceCount + 1;
	for (UINT i = 0; i < stackCount - 2; ++i)
	{
		for (UINT j = 0; j < sliceCount; ++j)
		{
			meshData.indices.push_back(baseIndex + i * ringVertexCount + j);
			meshData.indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			meshData.indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);

			meshData.indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);
			meshData.indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			meshData.indices.push_back(baseIndex + (i + 1)*ringVertexCount + j + 1);
		}
	}

	//
	// Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
	// and connects the bottom pole to the bottom ring.
	//

	// South pole vertex was added last.
	UINT southPoleIndex = (UINT)meshData.vertices.size() - 1;

	// Offset the indices to the index of the first vertex in the last ring.
	baseIndex = southPoleIndex - ringVertexCount;

	for (UINT i = 0; i < sliceCount; ++i)
	{
		meshData.indices.push_back(southPoleIndex);
		meshData.indices.push_back(baseIndex + i);
		meshData.indices.push_back(baseIndex + i + 1);
	}

	mMeshes[MeshType::Sphere] = meshData;
}

void GeometryGenerator::createPlane()
{
	const std::vector<Vertex> v =
	{
		{XMFLOAT3(-0.5f,0.0f,-0.5f),XMFLOAT2(0.0f,0.0f)},
		{XMFLOAT3(+0.5f,0.0f,-0.5f),XMFLOAT2(1.0f,0.0f)},
		{XMFLOAT3(+0.5f,0.0f,+0.5f),XMFLOAT2(1.0f,1.0f)},
		{XMFLOAT3(-0.5f,0.0f,+0.5f),XMFLOAT2(0.0f,1.0f)},
	};

	const std::vector<UINT> i =
	{
		0,2,1,
		0,3,2
	};

	mMeshes[MeshType::Plane].vertices = v;
	mMeshes[MeshType::Plane].indices = i;
}

void GeometryGenerator::createModel(const std::string & name)
{
	Mesh m;
	FileManager::LoadOBJModel(m, name);
	mModels[name] = m;
}