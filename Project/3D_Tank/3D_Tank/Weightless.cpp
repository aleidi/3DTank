#include "Weightless.h"
#include "Transform.h"

Weightless::Weightless()
{
}

void Weightless::onUpdate(const float& deltaTime)
{
	empty->getTransform()->rotateY(0.015);
}