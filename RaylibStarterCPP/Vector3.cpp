#include "Vector3.h"
#include <cmath>

MathClasses::Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

MathClasses::Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

std::string MathClasses::Vector3::ToString() const
{
	return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z);
}

float MathClasses::Vector3::Magnitude() const
{
	float magnitude = sqrt((x * x) + (y * y) + (z * z));
	return magnitude;
}

float MathClasses::Vector3::Dot(Vector3 o) const
{
	float dotProduct = (x * o.x) + (y * o.y) + (z * o.z);
	return dotProduct;
}

MathClasses::Vector3 MathClasses::Vector3::Normalised() const
{
	Vector3 temp = *this;
	temp.Normalise();
	return temp;
}

void MathClasses::Vector3::Normalise()
{
	float mag = this->Magnitude();
	if (mag > 0) {
		this->x /= mag;
		this->y /= mag;
		this->z /= mag;
	}
}

MathClasses::Vector3 MathClasses::Vector3::Cross(Vector3 o) const
{
	Vector3 newVec;
	newVec.x = ((y * o.z) - (z * o.y));
	newVec.y = ((z * o.x) - (x * o.z));
	newVec.z = ((x * o.y) - (y * o.x));
	return newVec;
}

MathClasses::Vector3 MathClasses::operator+(Vector3 a, Vector3 b)
{
	Vector3 newVec;
	newVec.x = a.x + b.x; 
	newVec.y = a.y + b.y;
	newVec.z = a.z + b.z;
	return newVec;
}

MathClasses::Vector3 MathClasses::operator-(Vector3 a, Vector3 b)
{
	Vector3 newVec;
	newVec.x = a.x - b.x;
	newVec.y = a.y - b.y;
	newVec.z = a.z - b.z;
	return newVec;
}

MathClasses::Vector3 MathClasses::operator*(Vector3 a, float b)
{
	Vector3 newVec;
	newVec.x = a.x * b;
	newVec.y = a.y * b;
	newVec.z = a.z * b;
	return newVec;
}

MathClasses::Vector3 MathClasses::operator*(float a, Vector3 b)
{
	Vector3 newVec;
	newVec.x = a * b.x;
	newVec.y = a * b.y;
	newVec.z = a * b.z;
	return newVec;
}

bool MathClasses::operator==(Vector3 a, Vector3 b)
{
	if (abs(a.x - b.x) < 0.001 && abs(a.y - b.y) < 0.001 && abs(a.z - b.z) < 0.001) {
		return true;
	}
	else {
		return false;
	}
}

bool MathClasses::operator!=(Vector3 a, Vector3 b)
{
	if (!(abs(a.x - b.x) < 0.001 && abs(a.y - b.y) < 0.001 && abs(a.z - b.z) < 0.001)) {
		return true;
	}
	else {
		return false;
	}
}
