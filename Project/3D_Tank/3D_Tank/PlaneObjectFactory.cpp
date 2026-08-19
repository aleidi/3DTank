#include "PlaneObjectFactory.h"
#include "ComponentBase.h"
#include "MeshBase.h"

PlaneObjectFactory::PlaneObjectFactory()
{
}

PlaneObjectFactory::~PlaneObjectFactory()
{
}

GameObject * PlaneObjectFactory::getObject()
{
	//ゲームオブジェクトを生成
	GameObject* obj = new GameObject();

	//描画コンポーネントを生成
	RenderComponent* rc = new RenderComponent(obj);
	Plane* plane = new Plane(rc);
	rc->setMesh(plane);
	//描画コンポーネントをゲームオブジェクトへ追加
	obj->addComponent(rc);

	return obj;
}
