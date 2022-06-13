#include "filters.h"

Filters::Filters()
{
    up   = 255;
    down = 0;
}

void Filters::redshift(Pixel& pix,int delta)
{
    pix.SetRed(pix.Red()+delta);
}
void Filters::greenshift(Pixel& pix,int delta)
{
    pix.SetGreen(pix.Green()+delta);
}
void Filters::blueshift(Pixel& pix,int delta)
{
    pix.SetBlue(pix.Blue()+delta);
}

void Filters::toBW(Pixel& pix)
{
    short Y = pix.Y();

    if (pix.Y() > 255)
        Y = 255;
    else if (pix.Y() < 0)
        Y = 0;
    pix.SetRed(Y);
    pix.SetGreen(Y);
    pix.SetBlue(Y);
}
QRgb Filters::round(Pixel& pix)
{
    int r,g,b;
//    QRgb rgb;
    // Threshold
    if (pix.Y() > up){
//        qDebug();
        QRgb rgb = qRgb(qRed(255),qGreen(255),qBlue(255));
        return rgb;
    }
    if (pix.Y() < down)
        return qRgb(qRed(0),qGreen(0),qBlue(0));

    // RED
    if (pix.Red() > 255)
        r = 255;
    else if (pix.Red() < 0)
        r = 0;
    else
        r = pix.Red();

    // GRREN
    if (pix.Green() > 255)
        g = 255;
    else if (pix.Green() < 0)
        g = 0;
    else
        g = pix.Green();

    //BLUE
    if (pix.Blue() > 255)
        b = 255;
    else if (pix.Blue() < 0)
        b = 0;
    else
        b = pix.Blue();

    return qRgb(r,g,b);
}
void Filters::Inverse(Pixel& pix)
{
    // RED
    if (pix.Red() > 255)
        pix.SetRed(-1 * (pix.Red()-255));
    else if (pix.Red() < 0)
        pix.SetRed(-pix.Red()+255);
    else
        pix.SetRed(255 - pix.Red());

    // GREEN
    if (pix.Green() > 255)
        pix.SetGreen(-1 * (pix.Green()-255));
    else if (pix.Green() < 0)
        pix.SetGreen(-pix.Green()+255);
    else
        pix.SetGreen(255 - pix.Green());

    //BLUE
    if (pix.Blue() > 255)
        pix.SetBlue(-1 * (pix.Blue()-255));
    else if (pix.Blue() < 0)
        pix.SetGreen(-pix.Blue()+255);
    else
        pix.SetBlue(255 - pix.Blue());

}

void Filters::log(Pixel& pix)
{
    pix.SetY(36*log2(pix.Y()));
}
void Filters::part (Pixel& pix){}
void Filters::power(Pixel& pix){}
