#include <fstream>
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
}

void FileManager::LoadOBJModel(GeometryGenerator::Mesh & mesh, const std::string & name, DirectX::XMVECTOR & maxPoint, DirectX::XMVECTOR & minPoint)
{
	char input;
	int flag = 0;
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
	DirectX::XMFLOAT3 max, min, temp;
	DirectX::XMVECTOR tempP;
	while (!fin.eof())
	{
		fin >> vertex.Position.x >> vertex.Position.y >> vertex.Position.z >> vertex.Texcoord.x >> vertex.Texcoord.y;
		if (flag == 0) {
			max.x = vertex.Position.x; max.y = vertex.Position.y; max.z = vertex.Position.z;
			min.x = vertex.Position.x; min.y = vertex.Position.y; min.z = vertex.Position.z;
			maxPoint = DirectX::XMLoadFloat3(&max); minPoint = DirectX::XMLoadFloat3(&min);
			flag++;
		}
		else {
			temp.x = vertex.Position.x; temp.y = vertex.Position.y; temp.z = vertex.Position.z;
			tempP = DirectX::XMLoadFloat3(&temp);
			maxPoint = DirectX::XMVectorMax(maxPoint, tempP);
			minPoint = DirectX::XMVectorMin(minPoint, tempP);
		}
		fin.get(input);
		while (input != '\n')
		{
			fin.get(input);
		}
		mesh.vertices.push_back(vertex);
		mesh.indices.push_back(index++);
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
