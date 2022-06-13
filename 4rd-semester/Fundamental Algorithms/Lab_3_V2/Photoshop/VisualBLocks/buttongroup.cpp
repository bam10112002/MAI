#include "buttongroup.h"

ButtonGroup::ButtonGroup(QWidget* parent) : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);
    author = new QPushButton(this);
    about  = new QPushButton(this);
    load   = new QPushButton(this);
    save   = new QPushButton(this);

    author->setText("About me");
    about->setText("About program");
    load->setText("Reload image");
    save->setText("Save Image");

    mainLayout->addWidget(author);
    mainLayout->addWidget(about);
    mainLayout->addWidget(load);
    mainLayout->addWidget(save);
    this->setLayout(mainLayout);

}

void ButtonGroup::authorClickedSlot(){ emit authorClicked(); }
void ButtonGroup::aboutClickedSlot (){ emit aboutClicked (); }
void ButtonGroup::loadClickedSlot  (){ emit loadClicked  (); }
void ButtonGroup::saveClickedSlot  (){ emit saveClicked  (); }

ButtonGroup::~ButtonGroup()
{
    delete mainLayout;
    delete author;
    delete about;
    delete load;
    delete save;
}

