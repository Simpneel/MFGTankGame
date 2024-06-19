#include "Bullet.h"

void Bullet::OnUpdate(float deltaTime)
{
	const float bulletSpeed = 750.0f;
	float bulletMove = 0.0f;
	if (IsKeyPressed(KEY_SPACE)) {
		bulletCount++;
	}
	if (bulletCount > 0) {
		bulletMove += bulletSpeed;
		this->Translate(GetForward() * (bulletMove * deltaTime));
		this->Draw();
	}
}

bool Bullet::CheckCollision(Rectangle colRec)
{
	if (CheckCollisionPointRec({ this->GetWorldPosition().x, this->GetWorldPosition().y }, colRec)) {
		return true;
	}
}
