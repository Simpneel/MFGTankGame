#include "Matrix3.h"

MathClasses::Matrix3::Matrix3() {
	this->m1 = 0.0f; // M 00
	this->m2 = 0.0f; // M 01
	this->m3 = 0.0f; // M 02
	this->m4 = 0.0f; // M 10
	this->m5 = 0.0f; // M 11
	this->m6 = 0.0f; // M 12
	this->m7 = 0.0f; // M 20
	this->m8 = 0.0f; // M 21
	this->m9 = 0.0f; // M 22
}

MathClasses::Matrix3::Matrix3(float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9) {
	this->m1 = a1;
	this->m2 = a2;
	this->m3 = a3;
	this->m4 = a4;
	this->m5 = a5;
	this->m6 = a6;
	this->m7 = a7;
	this->m8 = a8;
	this->m9 = a9;
}

MathClasses::Matrix3::Matrix3(float* v) {
	this->m1 = v[0];
	this->m2 = v[1];
	this->m3 = v[2];
	this->m4 = v[3];
	this->m5 = v[4];
	this->m6 = v[5];
	this->m7 = v[6];
	this->m8 = v[7];
	this->m9 = v[8];
}

std::string MathClasses::Matrix3::ToString() const {
	std::string newStr = std::to_string(m1) + ", " + std::to_string(m2) + ", " + std::to_string(m3) + ", " +
		std::to_string(m4) + ", " + std::to_string(m5) + ", " + std::to_string(m6) + ", " +
		std::to_string(m7) + ", " + std::to_string(m8) + ", " + std::to_string(m9);
	return newStr;
} 

MathClasses::Matrix3 MathClasses::Matrix3::MakeIdentity() {
	Matrix3 identityMatrix;
	identityMatrix.m1 = 1.0f; identityMatrix.m5 = 1.0f; identityMatrix.m9 = 1.0f;
	identityMatrix.m2 = 0.0f; identityMatrix.m3 = 0.0f; identityMatrix.m4 = 0.0f; identityMatrix.m6 = 0.0f; identityMatrix.m7 = 0.0f; identityMatrix.m8 = 0.0f;
	return identityMatrix;
}

MathClasses::Matrix3 MathClasses::Matrix3::MakeTranslation(float x, float y, float z) {
	return Matrix3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, x, y, z);
}

MathClasses::Matrix3 MathClasses::Matrix3::MakeTranslation(Vector3 v) {
	return Matrix3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, v.x, v.y, v.z);
}

MathClasses::Matrix3 MathClasses::Matrix3::MakeRotateX(float r)
{
	return Matrix3(1.0f, 0.0f, 0.0f, 0.0f, cos(r), -sin(r), 0.0f, sin(r), cos(r));
}

MathClasses::Matrix3 MathClasses::Matrix3::MakeRotateY(float r)
{
	return Matrix3(cos(r), 0.0f, sin(r), 0.0f, 1.0f, 0.0f, -sin(r), 0.0f, cos(r));
}

MathClasses::Matrix3 MathClasses::Matrix3::MakeRotateZ(float r)
{
	return Matrix3(cos(r), sin(r), 0.0f, -sin(r), cos(r), 0.0f, 0.0f, 0.0f, 1.0f);
}

MathClasses::Matrix3 MathClasses::Matrix3::MakeEuler(float x, float y, float z)
{
	Matrix3 pitch = MakeRotateX(x);
	Matrix3 yaw = MakeRotateY(y);
	Matrix3 roll = MakeRotateZ(z);
	return (roll * yaw * pitch);
}

MathClasses::Matrix3 MathClasses::Matrix3::MakeEuler(Vector3 e)
{
	Matrix3 pitch = MakeRotateX(e.x);
	Matrix3 yaw = MakeRotateY(e.y);
	Matrix3 roll = MakeRotateZ(e.z);
	return (roll * yaw * pitch);
}

MathClasses::Matrix3 MathClasses::Matrix3::MakeScale(float x, float y)
{
	return Matrix3(x, 0.0f, 0.0f, 0.0f, y, 0.0f, 0.0f, 0.0f, 1.0f);
}

MathClasses::Matrix3 MathClasses::Matrix3::MakeScale(float x, float y, float z)
{
	return Matrix3(x, 0.0f, 0.0f, 0.0f, y, 0.0f, 0.0f, 0.0f, z);
}

MathClasses::Matrix3 MathClasses::Matrix3::MakeScale(Vector3 s)
{
	return MakeScale(s.x, s.y, s.z);
}

MathClasses::Matrix3 MathClasses::Matrix3::Transposed()
{
	return Matrix3(m1, m4, m7, m2, m5, m8, m3, m6, m9);
}

MathClasses::Matrix3 MathClasses::operator*(Matrix3 a, Matrix3 b)
{
	return Matrix3(
		a.m1 * b.m1 + a.m4 * b.m2 + a.m7 * b.m3,
		a.m2 * b.m1 + a.m5 * b.m2 + a.m8 * b.m3,
		a.m3 * b.m1 + a.m6 * b.m2 + a.m9 * b.m3,

		a.m1 * b.m4 + a.m4 * b.m5 + a.m7 * b.m6,
		a.m2 * b.m4 + a.m5 * b.m5 + a.m8 * b.m6,
		a.m3 * b.m4 + a.m6 * b.m5 + a.m9 * b.m6,

		a.m1 * b.m7 + a.m4 * b.m8 + a.m7 * b.m9,
		a.m2 * b.m7 + a.m5 * b.m8 + a.m8 * b.m9,
		a.m3 * b.m7 + a.m6 * b.m8 + a.m9 * b.m9
		);
}

MathClasses::Vector3 MathClasses::operator*(Matrix3 a, Vector3 b)
{
	return Vector3(
		Vector3(a.m1, a.m4, a.m7).Dot(b), 
		Vector3(a.m2, a.m5, a.m8).Dot(b),
		Vector3(a.m3, a.m6, a.m9).Dot(b)
	);
}

bool MathClasses::operator==(Matrix3 a, Matrix3 b)
{
	if (abs(a.m1 - b.m1) < 0.001 && abs(a.m2 - b.m2) < 0.001 && abs(a.m3 - b.m3) < 0.001 && abs(a.m4 - b.m4) < 0.001 && abs(a.m5 - b.m5) < 0.001 && abs(a.m7 - b.m7) < 0.001 && abs(a.m8 - b.m8) < 0.001 && abs(a.m9 - b.m9) < 0.001) {
		return true;
	}
	else return false;
}

bool MathClasses::operator!=(Matrix3 a, Matrix3 b)
{
	if (!(abs(a.m1 - b.m1) < 0.001 && abs(a.m2 - b.m2) < 0.001 && abs(a.m3 - b.m3) < 0.001 && abs(a.m4 - b.m4) < 0.001 && abs(a.m5 - b.m5) < 0.001 && abs(a.m7 - b.m7) < 0.001 && abs(a.m8 - b.m8) < 0.001 && abs(a.m9 - b.m9) < 0.001)) {
		return true;
	}
	else return false;
}
