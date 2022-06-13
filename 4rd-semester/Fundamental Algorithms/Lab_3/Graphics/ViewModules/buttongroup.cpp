#include "buttongroup.h"

ButtonGroup::ButtonGroup(QWidget* parent) : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);
    author = new QPushButton(this);
    about  = new QPushButton(this);
    load   = new QPushButton(this);
    save   = new QPushButton(this);

//    QString style = new QString("border-radius: 10px");
    author->setText("About me");
    about->setText("About program");
    load->setText("Reload image");
    save->setText("Save Image");

    mainLayout->addWidget(author);
    mainLayout->addWidget(about);
    mainLayout->addWidget(load);
    mainLayout->addWidget(save);

}
ButtonGroup::~ButtonGroup()
{
    delete mainLayout;
    delete author;
    delete about;
    delete load;
    delete save;
}
