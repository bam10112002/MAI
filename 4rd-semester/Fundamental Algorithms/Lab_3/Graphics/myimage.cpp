#include "myimage.h"

MyImage::MyImage(QLabel* _label, QWidget* window) :
    rgb(this), threshold(this), brightness(this)
{
    fileName = QFileDialog::getOpenFileName(window,"Open Image", "C:/Users/Artem/Downloads", "Image Files (*.png *.jpg *.bmp)");
    img = new QImage(fileName);
    label = _label;

    if (img->width() > img->height())
        scaledFactor = label->width() * 1.0 / img->width();
    else
        scaledFactor = label->height() * 1.0 / img->height();


    imgMatrix = new Pixel*[img->height()];
    for(int y = 0; y < img->height(); y++)
    {
        imgMatrix[y] = new Pixel[img->width()];
        for(int x = 0; x < img->width(); x++)
        {
            imgMatrix[y][x] = img->pixel(x,y);
        }
    }
}

QPixmap MyImage::getPix()
{
    return QPixmap::fromImage(img->scaled(QSize(img->width() * scaledFactor, img->height() * scaledFactor)));
}
QImage MyImage::getImg()
{
    return *img;
//    return img->scaled(QSize(img->width() * scaledFactor, img->height() * scaledFactor));
}

int MyImage::width()
{
    return img->width();
}
int MyImage::height()
{
    return img->height();
}

void MyImage::ToBlackWhite()
{
    //Преобразование в ЧБ
    QRgb pb;
    int newPixel;
    for(int x=0; x<img->width();x++){
        for(int y=0; y<img->height(); y++){
            pb = img->pixel(x,y);
            newPixel = (qRed(pb) + qGreen(pb) + qBlue(pb))/3;
            img->setPixel(x,y,qRgb(newPixel, newPixel, newPixel));
        }
    }
}
void MyImage::Inverse()
{
    QRgb pb;
    for(int x = 0; x < img->width();x++){
            for(int y=0; y < img->height(); y++){
                pb = img->pixel(x,y);
                img->setPixel(x,y,qRgb(255 - qRed(pb),
                                       255 - qGreen(pb),
                                       255 - qBlue(pb)));
            }
    }
}

Pixel Pixel::operator = (QRgb rgb)
{
    this->red = qRed(rgb);
    this->blue = qBlue(rgb);
    this->green = qGreen(rgb);
    return *this;
}
Pixel::Pixel(int _red, int _green, int _blue)
{
    red = _red;
    green = _green;
    blue = _blue;
}
QRgb Pixel::getQrgb()
{
//    QRgb ret = QRgb(red, green, blue);
//    return ret;
}

inline int Fx(long long int cdf, long long int minCdf, unsigned long pix)
{
    return ((cdf - minCdf) * 1.0/(pix - 1))*255;
}
void MyImage::Best()
{
    QVector<long long int> redVec(256);
    QVector<long long int> greenVec(256);
    QVector<long long int> blueVec(256);

    long long int minRed = 256, minBlue = 256, minGreen = 256;

    QRgb pb;
    for(int x = 0; x < img->width();x++){
            for(int y=0; y < img->height(); y++){
                pb = img->pixel(x,y);
                redVec[qRed(pb)] += 1;
                greenVec[qGreen(pb)] += 1;
                blueVec[qBlue(pb)] += 1;
            }
    }

    for (int i = 1; i < 255; i++)
    {
        redVec[i] += redVec[i-1];
        greenVec[i] += greenVec[i-1];
        blueVec[i] += blueVec[i-1];

        if (redVec[i])
            minRed = std::min(redVec[i], minRed);
        if (blueVec[i])
            minBlue = std::min(blueVec[i], minBlue);
        if (greenVec[i])
            minGreen = std::min(greenVec[i], minGreen);
    }
    unsigned long pix = img->width() * img->height();

    pb = img->pixel(130, 100);

    for(int x = 0; x < img->width();x++){
            for(int y=0; y < img->height(); y++){
                pb = img->pixel(x,y);
                img->setPixel(x,y,qRgb(Fx(redVec[qRed(pb)], minRed, pix),
                                       Fx(greenVec[qGreen(pb)], minGreen, pix),
                                       Fx(blueVec[qBlue(pb)], minBlue, pix)));

            }
    }


}

MyImage::~MyImage()
{
    for(int y = 0; y < img->height(); y++)
        delete[] imgMatrix[y];
    delete[] imgMatrix;
}
