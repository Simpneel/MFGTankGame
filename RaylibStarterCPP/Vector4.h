#pragma once
#include <string>

namespace MathClasses
{
    struct Vector4
    {
        float x, y, z, w;

        Vector4();
        Vector4(float x, float y, float z, float w);

        std::string ToString() const;

        float Magnitude() const;
        float Dot(Vector4 o) const;
        Vector4 Normalised() const;
        void Normalise();
        Vector4 Cross(Vector4 o) const;

        friend Vector4 operator+(Vector4 a, Vector4 b);
        friend Vector4 operator-(Vector4 a, Vector4 b);
        friend Vector4 operator*(Vector4 a, float b);
        friend Vector4 operator*(float a, Vector4 b);

        friend bool operator==(Vector4 a, Vector4 b);
        friend bool operator!=(Vector4 a, Vector4 b);
	};
}