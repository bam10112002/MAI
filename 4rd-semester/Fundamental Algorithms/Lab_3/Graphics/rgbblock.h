#ifndef RGBBLOCK_H
#define RGBBLOCK_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>

class RgbBlock : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout* mainLayout;
    QVBoxLayout* redLayout;
    QVBoxLayout* greenLayout;
    QVBoxLayout* blueLayout;

    QSpacerItem* spacer;

    QSlider* red;
    QSlider* green;
    QSlider* blue;


    QLabel* redCircle;
    QLabel* greenCircle;
    QLabel* blueCircle;

public slots:
    void redSliderChanged(int);
    void greenSliderChanged(int);
    void blueSliderChanged(int);

public:
    RgbBlock();

signals:
     void redChanged(int);
     void greenChanged(int);
     void blueChanged(int);
};

#endif // RGBBLOCK_H
