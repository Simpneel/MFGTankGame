#include "Tank.h"

void Tank::OnUpdate(float deltaTime) 
{
	const float moveSpeed = 150.0f;
	const float rotateSpeed = 2.50f;
	float rotation = 0.0f;
	float yMove = 0.0f;
	if (Direction == 87) {
		yMove += moveSpeed;
	}
	if (Direction == 83) {
		yMove -= moveSpeed;
	}
	if (Direction == 65) {
		rotation -= rotateSpeed;
	}
	if (Direction == 68) {
		rotation += rotateSpeed;
	}

	MathClasses::Vector3 finalMove = GetForward() * (yMove * deltaTime);
	Translate(finalMove);
	
	Rotate(rotation * deltaTime);
}

