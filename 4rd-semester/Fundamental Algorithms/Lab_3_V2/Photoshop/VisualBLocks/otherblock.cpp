#include "otherblock.h"

OtherBlock::OtherBlock()
{
    mainLayout = new QVBoxLayout(this);
    inverse    = new QPushButton(this);
    whiteBlack = new QPushButton(this);
    beautify   = new QPushButton(this);

    inverse->setText("Inverse");
    connect(inverse, SIGNAL(clicked()), this, SLOT(inverseClickedSlot()));

    whiteBlack->setText("Black and White");
    connect(whiteBlack, SIGNAL(clicked()), this, SLOT(wbClickedSlot()));

    beautify->setText("Beautify (W/B)");
    connect(beautify, SIGNAL(clicked()), this, SLOT(beautifyClickedSlot()));


    mainLayout->addWidget(inverse);
    mainLayout->addWidget(whiteBlack);
}
OtherBlock::~OtherBlock()
{
    delete mainLayout;
    delete inverse;
    delete whiteBlack;
}

void OtherBlock::beautifyClickedSlot()
{
    emit beautifyClicked();
}

void OtherBlock::inverseClickedSlot()
{
    emit inverseClicked();
}
void OtherBlock::wbClickedSlot()
{
    emit wbClicked();
}
