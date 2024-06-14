#include "Bullet.h"

void Bullet::OnUpdate(float deltaTime)
{
	float bulletSpeed = 1000.0f;

	MathClasses::Vector3 finalMove = GetForward() * (bulletSpeed * deltaTime);
	Translate(finalMove);
}
