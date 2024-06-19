#include "Turret.h"

void Turret::OnUpdate(float deltaTime)
{
	const float rotateSpeed = 2.50f;
	float rotation = 0.0f;
	if (IsKeyDown(KEY_Q)) {
		rotation -= rotateSpeed;
	}
	else if (IsKeyDown(KEY_E)) {
		rotation += rotateSpeed;
	}
	Rotate(rotation * deltaTime);
}
