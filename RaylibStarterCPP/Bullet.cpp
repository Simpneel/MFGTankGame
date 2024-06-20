#include "Bullet.h"

void Bullet::OnUpdate(float deltaTime)
{
	const float bulletSpeed = 250.0f;
	this->Translate(GetForward() * (bulletSpeed * deltaTime));
}

bool Bullet::CheckCollision(Rectangle colRec)
{
	if (CheckCollisionPointRec({ this->GetWorldPosition().x, this->GetWorldPosition().y }, colRec)) {
		return true;
	}
}

bool Bullet::CheckCollision(Rectangle top, Rectangle bot, Rectangle left, Rectangle right)
{
	Vector2 tempVec = { this->GetWorldPosition().x, this->GetWorldPosition().y };
	if (CheckCollisionPointRec(tempVec, top)) return true;
	else if (CheckCollisionPointRec(tempVec, bot)) return true;
	else if (CheckCollisionPointRec(tempVec, left)) return true;
	else if (CheckCollisionPointRec(tempVec, right)) return true;
	else return false;
}
