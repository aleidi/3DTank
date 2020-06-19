#include "MovementTest.h"

MovementTest::MovementTest()
{

}

MovementTest::~MovementTest()
{

}

void MovementTest::Move(Vector3 value)
{
	getMoveComponent()->addForce(value);
}