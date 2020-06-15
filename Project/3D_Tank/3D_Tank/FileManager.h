#include "EngineCommon.h"
#include "GeometryGenerator.h"

class FileManager
{
public:
	static void LoadOBJModel(GeometryGenerator::Mesh& mesh, const std::string& name);
	static void LoadOBJModel(GeometryGenerator::Mesh& mesh, const std::string& name, DirectX::XMVECTOR& maxPoint, DirectX::XMVECTOR& minPoint);

	static wchar_t* GetTexture(const std::string& name);
};
