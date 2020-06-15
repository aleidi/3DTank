#include <fstream>

#include <DirectXMath.h>
#include "FileManager.h"

void FileManager::LoadOBJModel(GeometryGenerator::Mesh & mesh, const std::string & name)
{
	char input;
	GeometryGenerator::Vertex vertex;
	UINT index = 0;
	std::fstream fin;
	std::string path;
	path = ".\\Resource\\Model\\" + name + ".txt";
	fin.open(path);

	if (!fin.good())
	{
		return;
	}

	//fin.get(input);
	while (!fin.eof())
	{
		fin >> vertex.Position.x >> vertex.Position.y >> vertex.Position.z >> vertex.Texcoord.x >> vertex.Texcoord.y;
		fin.get(input);
		while (input != '\n')
		{
			fin.get(input);
		}
		mesh.vertices.push_back(vertex);
		mesh.indices.push_back(index++);
	}

	for (int i = 0; i < mesh.vertices.size() - 1;)
	{
		
		XMFLOAT3 p0 = mesh.vertices[i].Position;
		XMFLOAT3 p1 = mesh.vertices[i+1].Position;
		XMFLOAT3 p2 = mesh.vertices[i+2].Position;

		XMVECTOR v0 = XMLoadFloat3(&p0);
		XMVECTOR v1 = XMLoadFloat3(&p1);
		XMVECTOR v2 = XMLoadFloat3(&p2);

		XMVECTOR v01 = XMVectorSubtract(v1, v0);
		XMVECTOR v12 = XMVectorSubtract(v2, v1);

		XMVECTOR nor = XMVector3Cross(v01, v12);
		nor = XMVector3Normalize(nor);

		XMStoreFloat3(&mesh.vertices[i].Normal, nor);
		XMStoreFloat3(&mesh.vertices[i+1].Normal, nor);
		XMStoreFloat3(&mesh.vertices[i+2].Normal, nor);

		i += 3;
	}
}

wchar_t * FileManager::GetTexture(const std::string & name)
{
	std::string path;
	path = ".\\Resource\\Model\\" + name + ".dds";
	wchar_t* wc = new wchar_t[path.size() + 1];
	std::swprintf(wc, path.size() + 1, L"%S", path.c_str());
	return wc;
}
