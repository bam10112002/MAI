#include "pixel.h"

Pixel::Pixel(int _red, int _green, int _blue)
{
    red   = _red;
    green = _green;
    blue  = _blue;
}
Pixel::Pixel(const QRgb& rgb)
{
    red   = qRed(rgb);
    green = qGreen(rgb);
    blue  = qBlue(rgb);
}

// Get
int Pixel::Red() const   { return red;   }
int Pixel::Green() const { return green; }
int Pixel::Blue() const  { return blue;  }

int Pixel::Y() const
{
    return ( 0.2126 * red + 0.7152 * green + 0.0722 * blue );
}
int Pixel::U() const
{
    return (-0.0999 * red - 0.3360 * green + 0.4360 * blue );
}
int Pixel::V() const
{
    return ( 0.6150 * red - 0.5586 * green - 0.0563 * blue );
}

// Set
void Pixel::SetY(int _Y)
{
    int U = -0.0999 * red - 0.3360 * green + 0.4360 * blue;
    int V =  0.6150 * red - 0.5586 * green - 0.0563 * blue;

    red   = _Y + 1.2803 * V;
    green = _Y - 0.2148 * U - 0.3805 * V;
    blue  = _Y + 2.1279 * U;
}
void Pixel::SetRed (int R)   { red   = R; }
void Pixel::SetGreen (int G) { green = G; }
void Pixel::SetBlue  (int B) { blue  = B; }

// Sourse
int Pixel::Norm(int color) const
{
    if (color < 0)
        color = 0;
    if (color > 255)
        color = 255;
    
    return color;
}
