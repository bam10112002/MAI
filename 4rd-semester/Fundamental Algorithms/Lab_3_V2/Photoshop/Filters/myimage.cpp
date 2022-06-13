#include "myimage.h"

MyImage::MyImage()
{
    image = new QImage;
    pixelMatrix = nullptr;
    if (!(this->load()))
    {
        QMessageBox msgBox(QMessageBox::Warning,
                           QString::fromUtf8("Предупреждение"),
                           QString::fromUtf8("\n   Возникла ошибка открытия файла,\n"
                                             "возможно файл не был выбран,\n"
                                             "для исправления ошибки нажмите «reload».\n")
                           );
        msgBox.exec();
    }
}
MyImage::~MyImage()
{
    delete image;

    if (pixelMatrix)
    {
        for (int i = 0; i < image->width(); i++)
        {
            delete pixelMatrix[i];
        }
        delete pixelMatrix;
    }
}

bool MyImage::load()
{
    QString fileName = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.jpg *.png");
    if (fileName == "")
        return false;
    image->load(fileName);

    if (pixelMatrix)
    {
        for (int i = 0; i < image->width(); i++)
        {
            delete pixelMatrix[i];
        }
        delete pixelMatrix;
    }

    pixelMatrix = new Pixel*[image->height()];
    for (int i = 0; i < image->height(); i++)
    {
        pixelMatrix[i] = new Pixel[image->width()];
    }

    for (int i = 0; i < image->height(); i++)
    {
        for (int j = 0; j < image->width(); j++)
        {
            pixelMatrix[i][j] = Pixel(image->pixel(j,i));
        }
    }

    return true;
}
bool MyImage::save()const
{
    QString fileName = QFileDialog::getSaveFileName(0, "Open Dialog", "", "*.cpp *.h");
    if (fileName == "")
        return false;
    image->save(fileName);
    return true;
}
void MyImage::ChangeImage()
{
    for (int i = 0; i < image->height(); i++)
    {
        for (int j = 0; j < image->width(); j++)
        {
            image->setPixel(j,i,filters.round(pixelMatrix[i][j]));
        }
    }
}

const QImage& MyImage::Image() const
{
    return *image;
}

void MyImage::RedShift(int delta)
{
    for (int i = 0; i < image->height(); i++)
    {
        for (int j = 0; j < image->width(); j++)
        {
            filters.redshift(pixelMatrix[i][j], delta);
        }
    }
    this->ChangeImage();
}
void MyImage::GreenShift(int delta)
{
    for (int i = 0; i < image->height(); i++)
    {
        for (int j = 0; j < image->width(); j++)
        {
            filters.greenshift(pixelMatrix[i][j], delta);
        }
    }
    this->ChangeImage();
}
void MyImage::BlueShift(int delta)
{
    for (int i = 0; i < image->width(); i++)
    {
        for (int j = 0; j < image->height(); j++)
        {
            filters.blueshift(pixelMatrix[i][j], delta);
        }
    }
    this->ChangeImage();
}
void MyImage::BW()
{
    for (int i = 0; i < image->height(); i++)
    {
        for (int j = 0; j < image->width(); j++)
        {
            filters.toBW(pixelMatrix[i][j]);
        }
    }
    this->ChangeImage();
}
void MyImage::Inverse()
{
    for (int i = 0; i < image->height(); i++)
    {
        for (int j = 0; j < image->width(); j++)
        {
            filters.Inverse(pixelMatrix[i][j]);
        }
    }
    this->ChangeImage();
}
void MyImage::ThresholdUp(int val)
{
    filters.up = val;
    this->ChangeImage();
}
void MyImage::ThresholdDown(int val)
{
    filters.down = val;
    this->ChangeImage();
}
