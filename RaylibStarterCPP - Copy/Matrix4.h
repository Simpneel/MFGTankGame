#pragma once
#include <string>
#include "Vector3.h"
#include "Vector4.h"

namespace MathClasses
{
    struct Matrix4
    {
        float m1, m2, m3, m4, m5, m6, m7, m8, m9,
            m10, m11, m12, m13, m14, m15, m16;

        Matrix4();
        Matrix4(float a1, float a2, float a3, float a4, float a5,
            float a6, float a7, float a8, float a9, float a10,
            float a11, float a12, float a13, float a14, float a15,
            float a16);
        Matrix4(float* v);

        std::string ToString() const;

        static Matrix4 MakeIdentity();
        static Matrix4 MakeTranslation(float x, float y, float z);
        static Matrix4 MakeTranslation(struct Vector3 v);
        static Matrix4 MakeRotateX(float r);
        static Matrix4 MakeRotateY(float r);
        static Matrix4 MakeRotateZ(float r);
        static Matrix4 MakeEuler(float x, float y, float z);
        static Matrix4 MakeEuler(struct Vector3 e);
        static Matrix4 MakeScale(float x, float y);
        static Matrix4 MakeScale(float x, float y, float z);
        static Matrix4 MakeScale(struct Vector3 s);

        Matrix4 Transposed();

        friend Matrix4 operator*(Matrix4 a, Matrix4 b);
        friend struct Vector4 operator*(Matrix4 a, struct Vector4 b);

        friend bool operator==(Matrix4 a, Matrix4 b);
        friend bool operator!=(Matrix4 a, Matrix4 b);
	};
}