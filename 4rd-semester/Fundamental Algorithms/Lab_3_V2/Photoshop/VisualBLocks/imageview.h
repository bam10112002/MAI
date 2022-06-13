#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QPaintEvent>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QDir>
#include <QWidget>
#include <QDebug>

class ImageView : public QWidget
{
    Q_OBJECT
private:
    QLabel* imgLabel;
    int _width, _height;

public:
    ImageView(QWidget* parent, int w, int h);
    ~ImageView();
    void SetImage(QImage img);
    void SetImage(QPixmap img);
    void Resize(int w, int h);

public slots:
    void paintEvent(QPaintEvent *event);
};

#endif // IMAGEVIEW_H
