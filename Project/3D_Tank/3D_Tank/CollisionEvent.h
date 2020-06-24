#pragma once

class CollisionEvent {
public:
	CollisionEvent(){}
	virtual ~CollisionEvent(){}

	virtual void onTriggerEnter(){}
	virtual void onTriggerStay(){}
	virtual void onTriggerExit(){}
	virtual void onCollisionEnter(){}
	virtual void onCollisionStay(){}
	virtual void onCollisionExit(){}

	bool onTrigger;
	bool onCollision;

private:

};