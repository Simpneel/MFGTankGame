#pragma once
#include <cstdint>
#include <string>

namespace MathClasses
{
    using Byte = unsigned char;

    struct Colour
    {
        std::uint32_t colour;

        std::string ToString() const;

        Colour();
        Colour(Byte r, Byte g, Byte b, Byte a);

        Byte GetRed() const;
        Byte GetGreen() const;
        Byte GetBlue() const;
        Byte GetAlpha() const;

        void SetRed(Byte v);
        void SetGreen(Byte v);
        void SetBlue(Byte v);
        void SetAlpha(Byte v);

        Colour setGreenToRed(Colour colour);

        friend bool operator==(Colour a, Colour b);
        friend bool operator!=(Colour a, Colour b);
    };
}