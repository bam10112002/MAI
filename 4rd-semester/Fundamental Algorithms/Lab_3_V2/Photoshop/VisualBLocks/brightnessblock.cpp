#include "brightnessblock.h"

BrightnessBlock::BrightnessBlock() : QWidget()
{
    log   = new QPushButton(this);
    power = new QPushButton(this);
    parts = new QPushButton(this);

    mainLayout  = new QHBoxLayout(this);
    buttonGroup = new QVBoxLayout(this);

    slider = new QSlider(this);

    log->setText("Log");
    log->setFixedSize(log->width() * 0.75, log->height());
    connect(log, SIGNAL(clicked()), this, SLOT(logClickedSlot()));

    power->setText("Power");
    power->setFixedSize(power->width() * 0.75, power->height());
    connect(power, SIGNAL(clicked()), this, SLOT(PowerClickedSlot()));

    parts->setText("Parts");
    parts->setFixedSize(parts->width() * 0.75, parts->height());
    connect(parts, SIGNAL(clicked()), this, SLOT(PartsClickedSlot()));

    slider->setMaximum(100);
    slider->setMinimum(0);
    slider->setValue(0);

    mainLayout->addLayout(buttonGroup);
    mainLayout->addWidget(slider);

    buttonGroup->addWidget(log);
    buttonGroup->addWidget(power);
    buttonGroup->addWidget(parts);

}

BrightnessBlock::~BrightnessBlock()
{
    delete log;
    delete parts;
    delete power;
    delete buttonGroup;
    delete mainLayout;
    delete slider;
}

void BrightnessBlock::logClickedSlot()
{
    emit logClicked();
}
void BrightnessBlock::PowerClickedSlot()
{
    qDebug() << "BrightnessS::PowerClickedSlot()";
    emit PowerClicked();
}
void BrightnessBlock::PartsClickedSlot()
{
    emit PartsClicked();
}
