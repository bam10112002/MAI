#include "imageview.h"

ImageView::ImageView(QWidget* parent, int w, int h) : QWidget(parent)
{
    this->resize(w,h);
    width = w;
    height = h;
    imgLabel = new QLabel(this);
    imgLabel->setStyleSheet("background: gray;");
    imgLabel->resize(w,h);
}
ImageView::~ImageView()
{
    delete imgLabel;
}


void ImageView::SetImage(QImage img)
{
    img = img.scaled(width, height);
    imgLabel->setPixmap(QPixmap::fromImage(img));
}
void ImageView::SetImage(QPixmap img)
{
    img = img.scaled(width, height);
    imgLabel->setPixmap(img);
}
void ImageView::Resize(int w, int h)
{
    imgLabel->resize(w,h);
}
