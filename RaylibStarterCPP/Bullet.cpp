#include "Bullet.h"

void Bullet::OnUpdate(float deltaTime)
{
	const float bulletSpeed = 750.0f;
	float ySpeed = 0.0f;
	ySpeed += bulletSpeed;
	Translate(GetForward() * (ySpeed * deltaTime));
}

bool Bullet::CheckCollision(Rectangle colRec)
{
	if (CheckCollisionPointRec({ this->GetWorldPosition().x, this->GetWorldPosition().y }, colRec)) {
		return true;
	}
}
