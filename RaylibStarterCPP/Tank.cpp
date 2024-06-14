#include "Tank.h"

void Tank::OnUpdate(float deltaTime) 
{
	const float moveSpeed = 150.0f;
	const float rotateSpeed = 2.50f;
	float rotation = 0.0f;
	float yMove = 0.0f;
	if (IsKeyDown(KEY_W)) {
		yMove += moveSpeed;
	}
	if (IsKeyDown(KEY_S)) {
		yMove -= moveSpeed;
	}
	if (IsKeyDown(KEY_A)) {
		rotation += rotateSpeed;
	}
	if (IsKeyDown(KEY_D)) {
		rotation -= rotateSpeed;
	}

	MathClasses::Vector3 finalMove = GetForward() * (yMove * deltaTime);
	Translate(finalMove);
	
	Rotate(rotation * deltaTime);
}

