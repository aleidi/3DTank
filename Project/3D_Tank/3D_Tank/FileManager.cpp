#include <fstream>
#include <sstream>
#include <string>

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

void FileManager::LoadAIAttribute(std::map<int, AIAttribute>& map)
{
	std::ifstream fin(".\\Resource\\Configuration\\AIConfig.csv");
	std::string line;
	float config[14];

	if (fin.is_open())
	{
		fin >> line;
		while (fin >> line)
		{
			size_t position = 0;
			for (int i = 0; i < 14; ++i)
			{
				std::string str = line.substr(position, line.find(',', position));
				config[i] = (float)atof(str.c_str());
				position = line.find(',', position) + 1;
			}

			struct AIAttribute temp;
			temp.m_HP = (int)config[1];
			temp.m_AttackRangeRadiusSq = config[2];
			temp.m_PursuitRangeRadiusSq = config[3];
			temp.m_WanderRangeRadiusSq = config[4];
			temp.m_Mass = config[5];
			temp.m_MaxSpeed = config[6];
			temp.m_AttackTimeDelay = config[7];
			temp.m_WanderRadius = config[8];
			temp.m_WanderDistance = config[9];
			temp.m_WanderJitter = config[10];
			temp.m_ResetPoint.x = config[11];
			temp.m_ResetPoint.y = config[12];
			temp.m_ResetPoint.z = config[13];
			int index = (int)config[0];

			//FileManager::AIAtrributes[index] = temp;
			map.insert(std::pair<int, AIAttribute>(index, temp));
		}
	}
}

std::map<int, AIAttribute> FileManager::AIAttributes = FileManager::createAttributesMap();

std::map<int, AIAttribute> FileManager::createAttributesMap()
{
	std::map<int, AIAttribute> map;
	FileManager::LoadAIAttribute(map);
	return map;
}