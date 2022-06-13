#include "imageview.h"

ImageView::ImageView(QWidget* parent, int w, int h) : QWidget(parent)
{
    imgLabel = new QLabel(this);
    imgLabel->setPixmap(QPixmap::fromImage(QImage(":/img/Datasets/noimage.jpeg")));
    imgLabel->resize(this->width(), this->height());
}
ImageView::~ImageView()
{
    delete imgLabel;
}


void ImageView::paintEvent(QPaintEvent *event)
{
    imgLabel->resize(this->width(), this->height());
}


void ImageView::SetImage(QImage img)
{
    double scaledFactor = 1;
    if (img.width() > img.height())
        scaledFactor = this->width() * 1.0 / img.width();
    else
        scaledFactor = this->height() * 1.0 / img.height();

    img = img.scaled(img.width() * scaledFactor, img.height() * scaledFactor);
    imgLabel->setPixmap(QPixmap::fromImage(img));
    imgLabel->setStyleSheet("background: gray;");
}
void ImageView::SetImage(QPixmap img)
{
    double scaledFactor ;
    if (img.width() > img.height())
        scaledFactor = this->width() * 1.0 / img.width();
    else
        scaledFactor = this->height() * 1.0 / img.height();

    img = img.scaled(this->width() * scaledFactor, this->height() * scaledFactor);
    imgLabel->setPixmap(img);
    imgLabel->setStyleSheet("background: gray;");
}
void ImageView::Resize(int w, int h)
{
    imgLabel->resize(w,h);
}
