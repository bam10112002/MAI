#include "thresholdblock.h"

ThresholdBlock::ThresholdBlock() : QWidget()
{
    black = new QSlider(this);
    white = new QSlider(this);

    blackCircle = new QLabel(this);
    whiteCircle = new QLabel(this);

    spacer = new QSpacerItem(0, 30);

    mainLayout  = new QHBoxLayout(this);
    blackLayout   = new QVBoxLayout(this);
    whiteLayout = new QVBoxLayout(this);

    black->setMinimum(0);
    black->setMaximum(255);
    black->setValue(0);
    connect(black, SIGNAL(valueChanged(int)), this, SLOT(blackSliderChanged(int)));

    white->setMinimum(0);
    white->setMaximum(255);
    white->setValue(255);
    connect(white, SIGNAL(valueChanged(int)), this, SLOT(whiteSliderChanged(int)));

    blackCircle->setStyleSheet("border-radius: 8px; background: black;");
    blackCircle->setFixedSize(16,16);
    whiteCircle->setStyleSheet("border-radius: 8px; background: gray;");
    whiteCircle->setFixedSize(16,16);

    mainLayout->addLayout(blackLayout);
    mainLayout->addLayout(whiteLayout);

    blackLayout->addWidget(black);
    blackLayout->addSpacerItem(spacer);
    blackLayout->addWidget(blackCircle);
    whiteLayout->addWidget(white);
    whiteLayout->addSpacerItem(spacer);
    whiteLayout->addWidget(whiteCircle);

}

void ThresholdBlock::blackSliderChanged(int val)
{
    emit blackChanged(val);
}
void ThresholdBlock::whiteSliderChanged(int val)
{
    emit whiteChanged(val);
}
