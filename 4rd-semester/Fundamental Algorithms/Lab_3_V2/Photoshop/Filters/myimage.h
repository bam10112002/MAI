#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <QImage>
#include <QString>
#include <QList>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include <functional>
#include "Filters/pixel.h"
#include "filters.h"

class MyImage : public QObject
{   
    Q_OBJECT
private:
    QImage* image;
    Pixel** pixelMatrix;
    Filters filters;

    bool load();
    bool save() const;
    void ChangeImage();

public:
    MyImage();
    ~MyImage();
    const QImage& Image() const;

public slots:
    void RedShift(int);
    void GreenShift(int);
    void BlueShift(int);
    void BW();
    void Inverse();
    void ThresholdUp(int);
    void ThresholdDown(int);
};

#endif // MYIMAGE_H


//    class FilterBlock
//    {
//    public:
//        enum class Type { SIMPLE, COLOR };
//        Type tp;
//    public:
//        FilterBlock(Type _tp) { tp = _tp; }
//    };
//    class SimpleFilter : public FilterBlock
//    {
//    public:
//        SimpleFilter(FilterBlock::Type tp, std::function<int()> f)
//            : FilterBlock(tp)
//        {
//            func = f;
//        }
//        std::function<int()> func;
//    };
//    class ColorFilter : public FilterBlock
//    {
//    public:
//        ColorFilter(FilterBlock::Type tp, std::function<int(int)> f, int delta)
//            : FilterBlock(tp)
//        {
//            func = f;
//            colorDelta = delta;
//        }
//        int colorDelta;
//        std::function<int(int)> func;
//    };
