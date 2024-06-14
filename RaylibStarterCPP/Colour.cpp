#include "Colour.h"

std::string MathClasses::Colour::ToString() const
{
    std::string bitString;
    for (int i = 0; i < 4; ++i)
    {
        int byteShift = (3 - i) * 8;
        unsigned char bits = unsigned char(colour >> byteShift);
        for (int j = 0; j < 8; ++j)
        {
            std::uint32_t mask = 1 << (7 - j);
            bool isBitSet = (bits & mask) != 0;
            bitString += std::to_string(int(isBitSet));
        }
        bitString += " ";
    }
    return bitString;
}

MathClasses::Colour::Colour()
{
    colour = 0xff;
}

MathClasses::Colour::Colour(Byte r, Byte g, Byte b, Byte a)
{
    colour = (r << 24) | (g << 16) | (b << 8) | (a);
}

MathClasses::Byte MathClasses::Colour::GetRed() const
{
    return this->colour >> 24;
}

MathClasses::Byte MathClasses::Colour::GetGreen() const
{
    return this->colour >> 16;
}

MathClasses::Byte MathClasses::Colour::GetBlue() const
{
    return this->colour >> 8;
}

MathClasses::Byte MathClasses::Colour::GetAlpha() const
{
    return this->colour;
}

void MathClasses::Colour::SetRed(Byte v)
{
    colour &= 0x00FFFFFF;
    unsigned int temp = v;
    temp <<= 24;
    colour += temp;
}

void MathClasses::Colour::SetGreen(Byte v)
{
    colour &= 0xFF00FFFF;
    unsigned int temp = v;
    temp <<= 16;
    colour += temp;
}

void MathClasses::Colour::SetBlue(Byte v)
{
    colour &= 0xFFFF00FF;
    unsigned int temp = v;
    temp <<= 8;
    colour += temp;
}

void MathClasses::Colour::SetAlpha(Byte v)
{
    colour &= 0xFFFFFF00;
    unsigned int temp = v;
    colour += temp;
}

MathClasses::Colour MathClasses::Colour::setGreenToRed(Colour colour) {

    Colour newColour;
    newColour.colour = 0x00000000 | (colour.colour >> 8);
    newColour.colour &= 0x00FF0000;
    newColour.colour = (newColour.colour) | (colour.colour & 0x0000FFFF) | ((colour.colour << 8) & 0xFF000000);
    return newColour;
}

bool MathClasses::operator==(Colour a, Colour b)
{
    if (a.GetRed() == b.GetRed() && a.GetGreen() == b.GetGreen() && a.GetBlue() == b.GetBlue() && a.GetAlpha() == b.GetAlpha()) {
        return true;
    }
    else {
        return false;
    }
}

bool MathClasses::operator!=(Colour a, Colour b)
{
    if (!(a.GetRed() == b.GetRed() && a.GetGreen() == b.GetGreen() && a.GetBlue() == b.GetBlue() && a.GetAlpha() == b.GetAlpha())) {
        return true;
    }
    else {
        return false;
    }
}
