#include "rgbblock.h"

RgbBlock::RgbBlock() : QWidget()
{
    red   = new QSlider(this);
    green = new QSlider(this);
    blue  = new QSlider(this);

    redCircle   = new QLabel(this);
    greenCircle = new QLabel(this);
    blueCircle  = new QLabel(this);

    spacer = new QSpacerItem(0, 30);

    mainLayout  = new QHBoxLayout(this);
    redLayout   = new QVBoxLayout(this);
    greenLayout = new QVBoxLayout(this);
    blueLayout  = new QVBoxLayout(this);

    int maxVal = 250;
    red->setMinimum(-maxVal);
    red->setMaximum(maxVal);
    red->setValue(0);
    connect(red, SIGNAL(valueChanged(int)), this, SLOT(redSliderChanged(int)));

    green->setMinimum(-maxVal);
    green->setMaximum(maxVal);
    green->setValue(0);
    connect(green, SIGNAL(valueChanged(int)), this, SLOT(greenSliderChanged(int)));

    blue->setMinimum(-maxVal);
    blue->setMaximum(maxVal);
    blue->setValue(0);
    connect(blue, SIGNAL(valueChanged(int)), this, SLOT(blueSliderChanged(int)));

    redCircle->setStyleSheet("border-radius: 8px; background: red;");
    redCircle->setFixedSize(16,16);
    greenCircle->setStyleSheet("border-radius: 8px; background: green;");
    greenCircle->setFixedSize(16,16);
    blueCircle->setStyleSheet("border-radius: 8px; background: blue;");
    blueCircle->setFixedSize(16,16);

    mainLayout->addLayout(redLayout);
    mainLayout->addLayout(greenLayout);
    mainLayout->addLayout(blueLayout);

    redLayout->addWidget(red);
    redLayout->addSpacerItem(spacer);
    redLayout->addWidget(redCircle);

    greenLayout->addWidget(green);
    greenLayout->addSpacerItem(spacer);
    greenLayout->addWidget(greenCircle);

    blueLayout->addWidget(blue);
    blueLayout->addSpacerItem(spacer);
    blueLayout->addWidget(blueCircle);

    oldRed   = 0;
    oldGreen = 0;
    oldBlue  = 0;
}

void RgbBlock::redSliderChanged(int val)
{
    int delta = val - oldRed;
    oldRed = val;
    emit redChanged(delta);
}
void RgbBlock::greenSliderChanged(int val)
{
    int delta = val - oldGreen;
    oldGreen = val;
    emit greenChanged(delta);
}
void RgbBlock::blueSliderChanged(int val)
{
    int delta = val - oldBlue;
    oldBlue = val;
    emit blueChanged(delta);
}
