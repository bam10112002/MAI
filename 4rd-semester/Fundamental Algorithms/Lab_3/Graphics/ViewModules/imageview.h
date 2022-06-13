#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QWidget>
#include <QDebug>

class ImageView : public QWidget
{
    Q_OBJECT
private:
    QLabel* imgLabel;
    int width, height;

public:
    ImageView(QWidget* parent, int w, int h);
    ~ImageView();
    void SetImage(QImage img);
    void SetImage(QPixmap img);
    void Resize(int w, int h);
};

#endif // IMAGEVIEW_H
