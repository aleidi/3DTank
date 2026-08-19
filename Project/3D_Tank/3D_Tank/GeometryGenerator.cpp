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

void GeometryGenerator::getModel(Mesh & mesh, const std::string & name, DirectX::XMVECTOR & maxPoint, DirectX::XMVECTOR & minPoint)
{
	if (mModels[name].vertices.size() == 0 || mModels[name].indices.size() == 0)
	{
		createModel(name, maxPoint, minPoint);
	}
	mesh = mModels[name];
}

void GeometryGenerator::getUIPanel(Mesh & mesh)
{
	if (mMeshes[MeshType::Panel].vertices.size() == 0 && mMeshes[MeshType::Panel].indices.size() == 0)
	{
		createUIPanel();
	}
	mesh = mMeshes[MeshType::Panel];
}

void GeometryGenerator::getUIText(Mesh & mesh) noexcept
{
	if (mMeshes[MeshType::Text].vertices.size() == 0 && mMeshes[MeshType::Text].indices.size() == 0)
	{
		createUIText();
	}
	mesh = mMeshes[MeshType::Text];
}

void GeometryGenerator::getModelT(MeshT & mesh, const std::string & name) noexcept
{
	FileManager::LoadOBJModelWithTangent(mesh, name);
}

void GeometryGenerator::createCube()
{
	std::vector<Vertex> vertices =
	{
		{ XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f,1.0f,0.0f) },
		{ XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f,1.0f,0.0f) },
		{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f,1.0f,0.0f) },
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f,1.0f,0.0f) },

		{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f,-1.0f,0.0f) },
		{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f,-1.0f,0.0f) },
		{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f,-1.0f,0.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f,-1.0f,0.0f) },

		{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(-1.0f,0.0f,0.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(-1.0f,0.0f,0.0f) },
		{ XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(-1.0f,0.0f,0.0f) },
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(-1.0f,0.0f,0.0f) },

		{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(1.0f,0.0f,0.0f) },
		{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(1.0f,0.0f,0.0f) },
		{ XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(1.0f,0.0f,0.0f) },
		{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(1.0f,0.0f,0.0f) },

		{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f,0.0f,-1.0f) },
		{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f,0.0f,-1.0f) },
		{ XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f,0.0f,-1.0f) },
		{ XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f,0.0f,-1.0f) },

		{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f,0.0f,1.0f) },
		{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f,0.0f,1.0f) },
		{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f,0.0f,1.0f) },
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f,0.0f,1.0f) },
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
	// 上極からスタックに沿って頂点を生成する。
	//

	// 極点では、矩形テクスチャを球面へマッピングする際に、
	// 対応するテクスチャ上の点が一意に定まらないため、
	// テクスチャ座標に歪みが生じる。
	Vertex topVertex{ XMFLOAT3(0.0f, +radius, 0.0f), XMFLOAT2(0.0f, 0.0f) };
	Vertex bottomVertex{ XMFLOAT3(0.0f, -radius, 0.0f),XMFLOAT2(0.0f, 1.0f) };

	meshData.vertices.push_back(topVertex);

	float phiStep = XM_PI / stackCount;
	float thetaStep = 2.0f*XM_PI / sliceCount;

	// 各スタックリングの頂点を生成する（極点はリングに含めない）。
	for (UINT i = 1; i <= stackCount - 1; ++i)
	{
		float phi = i * phiStep;

		// リングの頂点。
		for (UINT j = 0; j <= sliceCount; ++j)
		{
			float theta = j * thetaStep;

			Vertex v;

			// 球面座標から直交座標へ変換
			v.Position.x = radius * sinf(phi)*cosf(theta);
			v.Position.y = radius * cosf(phi);
			v.Position.z = radius * sinf(phi)*sinf(theta);

			//// Pのthetaに関する偏微分
			//v.TangentU.x = -radius * sinf(phi)*sinf(theta);
			//v.TangentU.y = 0.0f;
			//v.TangentU.z = +radius * sinf(phi)*cosf(theta);

			//XMVECTOR T = XMLoadFloat3(&v.TangentU);
			//XMStoreFloat3(&v.TangentU, XMVector3Normalize(T));

			XMVECTOR p = XMLoadFloat3(&v.Position);
			XMStoreFloat3(&v.Normal, XMVector3Normalize(p));

			v.Texcoord.x = theta / XM_2PI;
			v.Texcoord.y = phi / XM_PI;

			meshData.vertices.push_back(v);
		}
	}

	meshData.vertices.push_back(bottomVertex);

	//
	// 上部スタックのインデックスを生成する。上部スタックは頂点バッファの先頭にあり、
	// 上極と最初のリングを接続する。
	//

	for (UINT i = 1; i <= sliceCount; ++i)
	{
		meshData.indices.push_back(0);
		meshData.indices.push_back(i + 1);
		meshData.indices.push_back(i);
	}

	//
	// 極点に接続しない内部スタックのインデックスを生成する。
	//

	// インデックスを最初のリングの先頭頂点までオフセットする。
	// 上極の頂点をスキップする。
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
	// 下部スタックのインデックスを生成する。下部スタックは頂点バッファの末尾にあり、
	// 下極と最後のリングを接続する。
	//

	// 南極の頂点は最後に追加されている。
	UINT southPoleIndex = (UINT)meshData.vertices.size() - 1;

	// インデックスを最後のリングの先頭頂点までオフセットする。
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
		{XMFLOAT3(-0.5f,0.0f,-0.5f),XMFLOAT2(0.0f,0.0f), XMFLOAT3(0.0f,1.0f,0.0f)},
		{XMFLOAT3(+0.5f,0.0f,-0.5f),XMFLOAT2(1.0f,0.0f), XMFLOAT3(0.0f,1.0f,0.0f)},
		{XMFLOAT3(+0.5f,0.0f,+0.5f),XMFLOAT2(1.0f,1.0f), XMFLOAT3(0.0f,1.0f,0.0f)},
		{XMFLOAT3(-0.5f,0.0f,+0.5f),XMFLOAT2(0.0f,1.0f), XMFLOAT3(0.0f,1.0f,0.0f)},
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

void GeometryGenerator::createModel(const std::string & name, DirectX::XMVECTOR & maxPoint, DirectX::XMVECTOR & minPoint)
{
	Mesh m;
	FileManager::LoadOBJModel(m, name, maxPoint, minPoint);
	mModels[name] = m;
}

void GeometryGenerator::createUIPanel()
{
	const std::vector<Vertex> v =
	{
		{XMFLOAT3(-0.5f,-0.5f,0.0f),XMFLOAT2(0.0f,1.0f)},
		{XMFLOAT3(0.5f,-0.5f,0.0f),XMFLOAT2(1.0f,1.0f)},
		{XMFLOAT3(0.5f,0.5f,0.0f),XMFLOAT2(1.0f,0.0f)},
		{XMFLOAT3(-0.5f,0.5f,0.0f),XMFLOAT2(0.0f,0.0f)},
	};

	const std::vector<UINT> i =
	{
		0,2,1,
		0,3,2
	};

	mMeshes[MeshType::Panel].vertices = v;
	mMeshes[MeshType::Panel].indices = i;
}

void GeometryGenerator::createUIText() noexcept
{
	const std::vector<Vertex> v =
	{
		{XMFLOAT3(-0.5f,-0.5f,0.0f),XMFLOAT2(0.0f,1.0f)},
		{XMFLOAT3(0.5f,-0.5f,0.0f),XMFLOAT2(1.0f,1.0f)},
		{XMFLOAT3(0.5f,0.5f,0.0f),XMFLOAT2(1.0f,0.0f)},
		{XMFLOAT3(-0.5f,0.5f,0.0f),XMFLOAT2(0.0f,0.0f)},
	};

	const std::vector<UINT> i =
	{
		0,2,1,
		0,3,2
	};

	mMeshes[MeshType::Text].vertices = v;
	mMeshes[MeshType::Text].indices = i;
}
