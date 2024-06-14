#include "Matrix4.h"

MathClasses::Matrix4::Matrix4() {
	this->m1 = 0.0f; // M 00
	this->m2 = 0.0f; // M 01
	this->m3 = 0.0f; // M 02
	this->m4 = 0.0f; // M 10
	this->m5 = 0.0f; // M 11
	this->m6 = 0.0f; // M 12
	this->m7 = 0.0f; // M 20
	this->m8 = 0.0f; // M 21
	this->m9 = 0.0f; // M 22
	this->m10 = 0.0f;
	this->m11 = 0.0f;
	this->m12 = 0.0f;
	this->m13 = 0.0f;
	this->m14 = 0.0f;
	this->m15 = 0.0f;
	this->m16 = 0.0f;
}

MathClasses::Matrix4::Matrix4(float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, float a10, float a11, float a12, float a13, float a14, float a15, float a16) {
	this->m1 = a1;
	this->m2 = a2;
	this->m3 = a3;
	this->m4 = a4;
	this->m5 = a5;
	this->m6 = a6;
	this->m7 = a7;
	this->m8 = a8;
	this->m9 = a9;
	this->m10 = a10;
	this->m11 = a11;
	this->m12 = a12;
	this->m13 = a13;
	this->m14 = a14;
	this->m15 = a15;
	this->m16 = a16;
}

MathClasses::Matrix4::Matrix4(float* v) {
	this->m1 = v[0];
	this->m2 = v[1];
	this->m3 = v[2];
	this->m4 = v[3];
	this->m5 = v[4];
	this->m6 = v[5];
	this->m7 = v[6];
	this->m8 = v[7];
	this->m9 = v[8];
	this->m10 = v[9];
	this->m11 = v[10];
	this->m12 = v[11];
	this->m13 = v[12];
	this->m14 = v[13];
	this->m15 = v[14];
	this->m16 = v[15];
}

std::string MathClasses::Matrix4::ToString() const {
	std::string newStr = std::to_string(m1) + ", " + std::to_string(m2) + ", " + std::to_string(m3) + ", " + std::to_string(m4) + ", " +
		std::to_string(m5) + ", " + std::to_string(m6) + ", " + std::to_string(m7) + ", " + std::to_string(m8) + ", " +
		std::to_string(m9) + ", " + std::to_string(m10) + ", " + std::to_string(m11) + ", " + std::to_string(m12) + ", " +
		std::to_string(m13) + ", " + std::to_string(m14) + ", " + std::to_string(m15) + ", " + std::to_string(m16);
	return newStr;
}


MathClasses::Matrix4 MathClasses::Matrix4::MakeIdentity() {
	return Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

MathClasses::Matrix4 MathClasses::Matrix4::MakeTranslation(float x, float y, float z) {
	return Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x, y, z, 1.0f
	);
}

MathClasses::Matrix4 MathClasses::Matrix4::MakeTranslation(Vector3 v) {
	return Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		v.x, v.y ,v.z, 1.0f
	);
}

MathClasses::Matrix4 MathClasses::Matrix4::MakeRotateX(float r) {
	return Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos(r), -sin(r), 0.0f,
		0.0f, sin(r), cos(r), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

MathClasses::Matrix4 MathClasses::Matrix4::MakeRotateY(float r) {
	return Matrix4(
		cos(r), 0.0f, sin(r), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sin(r), 0.0f, cos(r), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

MathClasses::Matrix4 MathClasses::Matrix4::MakeRotateZ(float r) {
	return Matrix4(
		cos(r), sin(r), 0.0f, 0.0f,
		-sin(r), cos(r), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

MathClasses::Matrix4 MathClasses::Matrix4::MakeEuler(float x, float y, float z) {
	Matrix4 pitch = MakeRotateX(x);
	Matrix4 yaw = MakeRotateY(y);
	Matrix4 roll = MakeRotateZ(z);
	return (roll * yaw * pitch);
}

MathClasses::Matrix4 MathClasses::Matrix4::MakeEuler(Vector3 e) {
	Matrix4 pitch = MakeRotateX(e.x);
	Matrix4 yaw = MakeRotateY(e.y);
	Matrix4 roll = MakeRotateZ(e.z);
	return (roll * yaw * pitch);
}

MathClasses::Matrix4 MathClasses::Matrix4::MakeScale(float x, float y) {
	return Matrix4(
		x, 0.0f, 0.0f, 0.0f,
		0.0f, y, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

MathClasses::Matrix4 MathClasses::Matrix4::MakeScale(float x, float y, float z)
{
	return Matrix4(
		x, 0.0f, 0.0f, 0.0f,
		0.0f, y, 0.0f, 0.0f,
		0.0f, 0.0f, z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

MathClasses::Matrix4 MathClasses::Matrix4::MakeScale(Vector3 s)
{
	return Matrix4(
		s.x, 0.0f, 0.0f, 0.0f,
		0.0f, s.y, 0.0f, 0.0f,
		0.0f, 0.0f, s.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

MathClasses::Matrix4 MathClasses::Matrix4::Transposed()
{
	return Matrix4(
		m1, m5, m9, m13, 
		m2, m6, m10, m14,
		m3, m7, m11, m15,
		m4, m8, m12, m16
	);
}

MathClasses::Matrix4 MathClasses::operator*(Matrix4 a, Matrix4 b)
{
	return Matrix4(
		a.m1 * b.m1 + a.m5 * b.m2 + a.m9 * b.m3 + a.m13 * b.m4,
		a.m2 * b.m1 + a.m6 * b.m2 + a.m10 * b.m3 + a.m14 * b.m4,
		a.m3 * b.m1 + a.m7 * b.m2 + a.m11 * b.m3 + a.m15 * b.m4,
		a.m4 * b.m1 + a.m8 * b.m2 + a.m12 * b.m3 + a.m16 * b.m4,

		a.m1* b.m5 + a.m5 * b.m6 + a.m9 * b.m7 + a.m13 * b.m8,
		a.m2* b.m5 + a.m6 * b.m6 + a.m10 * b.m7 + a.m14 * b.m8,
		a.m3* b.m5 + a.m7 * b.m6 + a.m11 * b.m7 + a.m15 * b.m8,
		a.m4* b.m5 + a.m8 * b.m6 + a.m12 * b.m7 + a.m16 * b.m8,

		a.m1* b.m9 + a.m5 * b.m10 + a.m9 * b.m11 + a.m13 * b.m12,
		a.m2* b.m9 + a.m6 * b.m10 + a.m10 * b.m11 + a.m14 * b.m12,
		a.m3* b.m9 + a.m7 * b.m10 + a.m11 * b.m11 + a.m15 * b.m12,
		a.m4* b.m9 + a.m8 * b.m10 + a.m12 * b.m11 + a.m16 * b.m12,

		a.m1* b.m13 + a.m5 * b.m14 + a.m9 * b.m15 + a.m13 * b.m16,
		a.m2* b.m13 + a.m6 * b.m14 + a.m10 * b.m15 + a.m14 * b.m16,
		a.m3* b.m13 + a.m7 * b.m14 + a.m11 * b.m15 + a.m15 * b.m16,
		a.m4* b.m13 + a.m8 * b.m14 + a.m12 * b.m15 + a.m16 * b.m16
	);
}

MathClasses::Vector4 MathClasses::operator*(Matrix4 a, Vector4 b)
{
	Vector4 newVec;
	newVec.x = a.m1 * b.x + a.m5 * b.y + a.m9 * b.z + a.m13 * b.w;
	newVec.y = a.m2 * b.x + a.m6 * b.y + a.m10 * b.z + a.m14 * b.w;
	newVec.z = a.m3 * b.x + a.m7 * b.y + a.m11 * b.z + a.m15 * b.w;
	newVec.w = a.m4 * b.x + a.m8 * b.y + a.m12 * b.z + a.m16 * b.w;
	return newVec;
	/*return Vector4(
		a.m1 * b.x + a.m2 * b.y + a.m3 * b.z + a.m4 * b.w,
		a.m5 * b.x + a.m6 * b.y + a.m7 * b.z + a.m8 * b.w,
		a.m9 * b.x + a.m10 * b.y + a.m11 * b.z + a.m12 * b.w,
		a.m13 * b.x + a.m14 * b.y + a.m15 * b.z + a.m16 * b.w  
	);*/
}

bool MathClasses::operator==(Matrix4 a, Matrix4 b)
{
	if (abs(a.m1 - b.m1) < 0.001 && abs(a.m2 - b.m2) < 0.001 && abs(a.m3 - b.m3) < 0.001 && abs(a.m4 - b.m4) < 0.001 && abs(a.m5 - b.m5) < 0.001 && abs(a.m7 - b.m7) < 0.001 && abs(a.m8 - b.m8) < 0.001 && abs(a.m9 - b.m9) < 0.001 && abs(a.m10 - b.m10) < 0.001 && abs(a.m11 - b.m11) < 0.001 && abs(a.m12 - b.m12) < 0.001 && abs(a.m13 - b.m13) < 0.001 && abs(a.m14 - b.m14) < 0.001 && abs(a.m15 - b.m15) < 0.001 && abs(a.m16 - b.m16) < 0.001) {
		return true;
	}
	else return false;
}

bool MathClasses::operator!=(Matrix4 a, Matrix4 b)
{
	if (!(abs(a.m1 - b.m1) < 0.001 && abs(a.m2 - b.m2) < 0.001 && abs(a.m3 - b.m3) < 0.001 && abs(a.m4 - b.m4) < 0.001 && abs(a.m5 - b.m5) < 0.001 && abs(a.m7 - b.m7) < 0.001 && abs(a.m8 - b.m8) < 0.001 && abs(a.m9 - b.m9) < 0.001 && abs(a.m10 - b.m10) < 0.001 && abs(a.m11 - b.m11) < 0.001 && abs(a.m12 - b.m12) < 0.001 && abs(a.m13 - b.m13) < 0.001 && abs(a.m14 - b.m14) < 0.001 && abs(a.m15 - b.m15) < 0.001 && abs(a.m16 - b.m16) < 0.001)) {
		return true;
	}
	else return false;
}
