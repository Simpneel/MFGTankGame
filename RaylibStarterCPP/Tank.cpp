#include "Tank.h"

void Tank::OnUpdate(float deltaTime) 
{
	const float moveSpeed = 150.0f;
	float yMove = 0.0f;
	if (IsKeyDown(KEY_W)) {
		yMove += moveSpeed;
	}
	if (IsKeyDown(KEY_S)) {
		yMove -= moveSpeed;
	}

	MathClasses::Vector3 finalMove = GetForward() * (yMove * deltaTime);
	Translate(finalMove);
}
