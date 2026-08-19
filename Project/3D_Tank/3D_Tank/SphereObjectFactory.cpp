#include "SphereObjectFactory.h"
#include "ComponentBase.h"
#include "MeshBase.h"

SphereObjectFactory::SphereObjectFactory() {
}

SphereObjectFactory::~SphereObjectFactory() {
}

GameObject* SphereObjectFactory::getObject() {
	//ゲームオブジェクトを生成
	GameObject* obj = new GameObject();

	//描画コンポーネントを生成
	RenderComponent* rc = new RenderComponent(obj);
	Sphere* sphere = new Sphere(rc);
	rc->setMesh(sphere);
	//描画コンポーネントをゲームオブジェクトへ追加
	obj->addComponent(rc);

	return obj;
}