#include "Vector4.h"

MathClasses::Vector4::Vector4()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

MathClasses::Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

std::string MathClasses::Vector4::ToString() const
{
	return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w);
}

float MathClasses::Vector4::Magnitude() const
{
	float mag = sqrt((x * x) + (y * y) + (z * z) + (w * w));
	return mag;
}

float MathClasses::Vector4::Dot(Vector4 o) const
{
	float dotProduct = (x * o.x) + (y * o.y) + (z * o.z) + (w * o.w);
	return dotProduct;
}

MathClasses::Vector4 MathClasses::Vector4::Normalised() const
{
	Vector4 temp = *this;
	temp.Normalise();
	return temp;
}

void MathClasses::Vector4::Normalise()
{
	float mag = this->Magnitude();
	if (mag > 0.0f) {
		this->x = this->x / mag;
		this->y = this->y / mag;
		this->z = this->z / mag;
		this->w = this->w / mag;
	}
}

MathClasses::Vector4 MathClasses::Vector4::Cross(Vector4 o) const
{
	Vector4 newVec;
	newVec.x = ((y * o.z) - (z * o.y));
	newVec.y = ((z * o.x) - (x * o.z));
	newVec.z = ((x * o.y) - (y * o.x));
	newVec.w = 0;
	return newVec;
}

MathClasses::Vector4 MathClasses::operator+(Vector4 a, Vector4 b)
{
	Vector4 newVec;
	newVec.x = a.x + b.x;
	newVec.y = a.y + b.y;
	newVec.z = a.z + b.z;
	newVec.w = a.w + b.w;
	return newVec;
}

MathClasses::Vector4 MathClasses::operator-(Vector4 a, Vector4 b)
{
	Vector4 newVec;
	newVec.x = a.x - b.x;
	newVec.y = a.y - b.y;
	newVec.z = a.z - b.z;
	newVec.w = a.w - b.w;
	return newVec;
}

MathClasses::Vector4 MathClasses::operator*(Vector4 a, float b)
{
	Vector4 newVec;
	newVec.x = a.x * b;
	newVec.y = a.y * b;
	newVec.z = a.z * b;
	newVec.w = a.w * b;
	return newVec;
}

MathClasses::Vector4 MathClasses::operator*(float a, Vector4 b)
{
	Vector4 newVec;
	newVec.x = a * b.x;
	newVec.y = a * b.y;
	newVec.z = a * b.z;
	newVec.w = a * b.w;
	return newVec;
}

bool MathClasses::operator==(Vector4 a, Vector4 b)
{
	if (abs(a.x - b.x) < 0.001 && abs(a.y - b.y) < 0.001 && abs(a.z - b.z) < 0.001 && abs(a.w - b.w) < 0.001) {
		return true;
	}
	else {
		return false;
	}
}

bool MathClasses::operator!=(Vector4 a, Vector4 b)
{
	if (!(abs(a.x - b.x) < 0.001 && abs(a.y - b.y) < 0.001 && abs(a.z - b.z) < 0.001 && abs(a.w - b.w) < 0.001)) {
		return true;
	}
	else {
		return false;
	}
}


