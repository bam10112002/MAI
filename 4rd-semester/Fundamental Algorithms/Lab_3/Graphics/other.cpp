#include "other.h"

Other::Other()
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
Other::~Other()
{
    delete mainLayout;
    delete inverse;
    delete whiteBlack;
}

void Other::beautifyClickedSlot()
{
    emit beautifyClicked();
}

void Other::inverseClickedSlot()
{
    emit inverseClicked();
}
void Other::wbClickedSlot()
{
    emit wbClicked();
}
