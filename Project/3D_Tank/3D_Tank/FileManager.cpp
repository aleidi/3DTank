#include <fstream>
#include "FileManager.h"

void FileManager::LoadOBJModel(GeometryGenerator::Mesh & mesh, const std::string & name)
{
	char input;
	GeometryGenerator::Vertex vertex;
	UINT index = 0;
	std::fstream fin;
	std::string path;
	path = ".\\Resource\\Model\\" + name;
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

wchar_t * FileManager::GetTexture(const std::string & name)
{
	std::string path;
	path = ".\\Resource\\Model\\" + name + ".dds";
	wchar_t* wc = new wchar_t[path.size() + 1];
	std::swprintf(wc, path.size() + 1, L"%S", path.c_str());
	return wc;
}
