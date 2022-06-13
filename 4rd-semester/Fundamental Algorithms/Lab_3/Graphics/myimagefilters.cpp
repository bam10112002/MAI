#include "myimage.h"

inline int8_t normColor(int color)
{
    if (color > 255)
        color = 255;
    else if (color < 0)
        color = 0;
    return color;
}

// RGB
RGB::RGB(MyImage* img)
{
    image = img;
}
void RGB::SetRed(int count)
{
    // Смещение к красному
    QRgb pb;
    int newPixel;
    Pixel pix(0,0,0);
    int delta = count - oldRed;

    for(int x = 0; x < image->img->width(); x++){
            for(int y = 0; y < image->height(); y++){
                pix = image->imgMatrix[y][x];
                newPixel = pix.red + delta;
                image->imgMatrix[y][x] = Pixel(newPixel, pix.green, pix.blue);
                image->img->setPixel(x,y,qRgb(normColor(newPixel), normColor(pix.green), normColor(pix.blue)));
            }
    }
    oldRed = count;
}
void RGB::SetBlue(int count)
{
    // Смещение к синему
    int newPixel;
    Pixel pix;
    int delta = count - oldBlue;

    for(int x=0; x<image->img->width();x++){
            for(int y=0; y<image->height(); y++){
                pix = image->imgMatrix[y][x];
                newPixel = pix.blue + delta;
                image->imgMatrix[y][x] = Pixel(pix.red, pix.green, newPixel);
                image->img->setPixel(x,y,qRgb(normColor(pix.red), normColor(pix.green), normColor(newPixel)));
            }
    }
    oldBlue = count;
}
void RGB::SetGreen(int count)
{
    // Смещение к зеленому
    int newPixel;
    Pixel pix;
    int delta = count - oldGreen;

    for(int x=0; x<image->img->width();x++){
            for(int y=0; y<image->height(); y++){
                pix = image->imgMatrix[y][x];
                newPixel = pix.green + delta;
                image->imgMatrix[y][x] = Pixel(pix.red, newPixel, pix.blue);
                image->img->setPixel(x,y,qRgb(normColor(pix.red), normColor(newPixel), normColor(pix.blue)));
            }
    }
    oldGreen = count;
}


//Threshold
Threshold::Threshold(MyImage* _image)
{
    image = _image;
    upLimit = 255;
    bottomLimit = 0;
}
void Threshold::setUp(int val)
{
    upLimit = val;
    QRgb pb;
    Pixel pix;
    int Y;

    for(int x=0; x<image->img->width();x++){
            for(int y=0; y<image->height(); y++){
                pix = image->imgMatrix[y][x];
                Y = 0.3*pix.red+0.59*pix.green+0.11*pix.blue;
                if (Y > upLimit)
                    image->img->setPixel(x,y,qRgb(255, 255, 255));
                else
                    image->img->setPixel(x,y,qRgb(pix.red,
                                    pix.green, pix.blue));
            }
    }

}
void Threshold::setBottom(int val)
{
    bottomLimit = val;
    Pixel pix;
    int Y;

    for(int x = 0; x < image->img->width(); x++)
    {
            for(int y = 0; y < image->height(); y++)
            {
                pix = image->imgMatrix[y][x];
                Y = 0.3*pix.red + 0.59*pix.green + 0.11*pix.blue;
                if (Y < bottomLimit)
                    image->img->setPixel(x,y,qRgb(0, 0, 0));
                else
                    image->img->setPixel(x,y,qRgb(pix.red,
                                    pix.green, pix.blue));
//                image->imgMatrix =
            }
    }
}


// Brightness
Brightness::Brightness(MyImage* _image)
{
    image = _image;
}

void Brightness::Log()
{
    Pixel pix;
    int c = 50;
    for(int x = 0; x < image->img->width(); x++)
    {
            for(int y = 0; y < image->height(); y++)
            {
                pix = image->imgMatrix[y][x];
                pix = Pixel(c * std::log10(pix.red), c * std::log10(pix.green), c * std::log10(pix.blue));
                image->imgMatrix[y][x] = pix;
                image->img->setPixel(x,y,qRgb(normColor(pix.red), normColor(pix.blue), normColor(pix.blue)));
            }
    }

}
void Brightness::Power()
{
    Pixel pix;
    double c = 0.002, g = 2.1;
    for(int x = 0; x < image->img->width(); x++)
    {
            for(int y = 0; y < image->height(); y++)
            {
                pix = image->imgMatrix[y][x];
                pix = Pixel(c * std::pow(pix.red, g), c * std::pow(pix.green, g), c * std::pow(pix.blue, g));
                image->imgMatrix[y][x] = pix;
                image->img->setPixel(x,y,qRgb(normColor(pix.red), normColor(pix.blue), normColor(pix.blue)));
            }
    }
}
