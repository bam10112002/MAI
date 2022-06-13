#ifndef PIXEL_H
#define PIXEL_H

#include <QImage>

class Pixel
{
    int red;   // R = Y + 1.2803 V
    int green; // G = Y - 0.2148 U - 0.3805 V;
    int blue;  // B = Y + 2.1279 U;

public:
    Pixel(){}
    Pixel(int _red, int _green, int _blue);
    Pixel(const QRgb&);

    // Get
    int Red()   const;
    int Green() const;
    int Blue()  const;

    int Y() const;
    int U() const;
    int V() const;

    // Set
    void SetY     (int);
    void SetRed   (int);
    void SetGreen (int);
    void SetBlue  (int);

    // Sourse
    int Norm(int color) const;
};

#endif // PIXEL_H
