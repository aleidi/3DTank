#include "EngineCommon.h"
#include "GeometryGenerator.h"

struct AIAttribute
{
	int m_HP;
	float m_AttackRangeRadiusSq;
	float m_PursuitRangeRadiusSq;
	float m_WanderRangeRadiusSq;

	float m_Mass;
	float m_MaxSpeed;
	float m_AttackTimeDelay;
	//float m_MaxForce;
	//float m_MaxTurnRate;

	float m_WanderRadius;
	float m_WanderDistance;
	float m_WanderJitter;

	Vector3 m_ResetPoint;
};

enum Language { CN, US };

class FileManager
{
public:
	static void LoadOBJModel(GeometryGenerator::Mesh& mesh, const std::string& name);
	static void LoadOBJModel(GeometryGenerator::Mesh& mesh, const std::string& name, DirectX::XMVECTOR& maxPoint, DirectX::XMVECTOR& minPoint);

	static wchar_t* GetTexture(const std::string& name);

	// AI configuration map
	static void LoadAIAttribute(std::map<int, AIAttribute>& map);
	static std::map<int, AIAttribute> createAttributesMap();
	static std::map<int, AIAttribute> AIAttributes;

	// Localization configuration map
	static std::map<int, std::wstring> LoadLocalization_US();
	static std::map<int, std::wstring> LoadLocalization_CN();
	static void changeLanguage(Language l);
	static std::map<int, std::wstring> localization;
};