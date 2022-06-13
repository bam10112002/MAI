#ifndef FILTERS_H
#define FILTERS_H

#include <QImage>
#include <cmath>
#include "pixel.h"

class Filters
{
public:
    Filters();
    int up, down;
    static void redshift(Pixel& pix,int delta);
    static void greenshift(Pixel& pix,int delta);
    static void blueshift(Pixel& pix,int delta);

    static void toBW(Pixel& pix);
    QRgb round(Pixel& pix);
    static void Inverse(Pixel& pix);

    static void log  (Pixel& pix);
    static void part (Pixel& pix);
    static void power(Pixel& pix);
};

#endif // FILTERS_H
