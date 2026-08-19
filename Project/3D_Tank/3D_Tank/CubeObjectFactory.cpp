#include "CubeObjectFactory.h"
#include "ComponentBase.h"
#include "MeshBase.h"

CubeObjectFactory::CubeObjectFactory() {
}

CubeObjectFactory::~CubeObjectFactory() {
}

GameObject* CubeObjectFactory::getObject() {
	// ゲームオブジェクトを生成
	GameObject* obj = new GameObject();

	// 描画コンポーネントを生成
	RenderComponent* rc = new RenderComponent(obj);
	Cube* cube = new Cube(rc);
	rc->setMesh(cube);
	// 描画コンポーネントをゲームオブジェクトに追加
	obj->addComponent(rc);

	return obj;
}