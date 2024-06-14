#pragma once
#include <string>
#include "Vector3.h"

namespace MathClasses
{
    struct Matrix3
    {
        float m1, m2, m3, m4, m5, m6, m7, m8, m9;

        Matrix3();
        Matrix3(float a1, float a2, float a3, float a4, float a5,
            float a6, float a7, float a8, float a9);
        Matrix3(float* v);

        std::string ToString() const;

        static Matrix3 MakeIdentity();
        static Matrix3 MakeTranslation(float x, float y, float z);
        static Matrix3 MakeTranslation(struct Vector3 v);
        static Matrix3 MakeRotateX(float r);
        static Matrix3 MakeRotateY(float r);
        static Matrix3 MakeRotateZ(float r);
        static Matrix3 MakeEuler(float x, float y, float z);
        static Matrix3 MakeEuler(struct Vector3 e);
        static Matrix3 MakeScale(float x, float y);
        static Matrix3 MakeScale(float x, float y, float z);
        static Matrix3 MakeScale(struct Vector3 s);

        Matrix3 Transposed();

        friend Matrix3 operator*(Matrix3 a, Matrix3 b);
        friend struct Vector3 operator*(Matrix3 a, struct Vector3 b);

        friend bool operator==(Matrix3 a, Matrix3 b);
        friend bool operator!=(Matrix3 a, Matrix3 b);
	};
}