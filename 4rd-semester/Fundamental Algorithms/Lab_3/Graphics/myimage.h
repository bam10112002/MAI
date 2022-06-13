#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <QImage>
#include <QString>
#include <QPixmap>
#include <QFileDialog>
#include <QLabel>
#include <QWidget>
#include <QVector>
#include <algorithm>

#include <math.h>
// предопределение
class MyImage;
class Threshold;
class RGB;
class Other;
class Pixel;
class Brightness;

// Основа

class Threshold
{
private:
    MyImage* image;
    int upLimit;
    int bottomLimit;

public:
    Threshold(MyImage*);
    void setUp(int);
    void setBottom(int);
};

class RGB
{
private:
    MyImage* image;
    int oldRed;
    int oldGreen;
    int oldBlue;

public:
    RGB(MyImage*);
    void SetRed(int count);
    void SetBlue(int count);
    void SetGreen(int count);
};

class Brightness
{
private:
    MyImage* image;

public:
    Brightness(MyImage*);

    void Log();
    void Power();
};

class Pixel
{
public:
    int red, green, blue;
    Pixel(int _red, int _green, int _blue);
    Pixel(){}
    Pixel operator = (QRgb);
    QRgb getQrgb();
};

class MyImage
{
private:
    QImage* img;
    Pixel** imgMatrix;
    QLabel* label;
    QString fileName;
    double scaledFactor;

public:

    RGB rgb;
    Threshold threshold;
    Brightness brightness;

    MyImage(QLabel* _label, QWidget* window);
    ~MyImage();

    QPixmap getPix();
    QImage getImg();
    int width();
    int height();

    void ToBlackWhite();
    void Inverse();
    void Best();
    void Black();

    friend class RGB;
    friend class Threshold;
    friend class Other;
    friend class Brightness;
};


#endif // MYIMAGE_H
