#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow)
{
    // Заметки:
    // - Почему то не реботают лэйауты в MainWindow,
    //      перешел на относительные координаты.


    ui->setupUi(this);

    buttons    = new ButtonGroup(this);
    imageView  = new ImageView(this,0,0);
    mainLayout = new QHBoxLayout();
    leftLayout = new QVBoxLayout();
    right      = new RightBlock(this);

    myImage = new MyImage();
    connect(right, &RightBlock::RedSliderChangedSignal  , myImage, &MyImage::RedShift);
    connect(right, &RightBlock::GreenSliderChangedSignal, myImage, &MyImage::GreenShift);
    connect(right, &RightBlock::BlueSliderChangedSignal , myImage, &MyImage::BlueShift);
    connect(right, &RightBlock::InverseClickedSignal,           myImage, &MyImage::Inverse);
    connect(right, &RightBlock::WBClickedSignal,                myImage, &MyImage::BW);

//    connect(right, &RightBlock::InverseClicked,           this, &MainWindow::updateImage);
//    connect(right, &RightBlock::WBClicked,                this, &MainWindow::updateImage);

//    connect(right, &RightBlock::RedSliderChangedSignal, this, &MainWindow::updateImage);

    buttons->resize(this->width()*0.6 , this->height() * 0.1);
    connect (buttons, &ButtonGroup::authorClicked, this, &MainWindow::aboutClickedSlot);
    connect (buttons, &ButtonGroup::aboutClicked , this, &MainWindow::aboutClickedSlot);
    connect (buttons, &ButtonGroup::loadClicked  , this, &MainWindow::loadClickedSlot );
    connect (buttons, &ButtonGroup::saveClicked  , this, &MainWindow::saveClickedSlot );


    mainLayout->addLayout(leftLayout);
    leftLayout->addWidget(imageView);
    leftLayout->addWidget(buttons);
    mainLayout->addWidget(right);


    this->setLayout(mainLayout);
    this->resize(1000, 600);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED (event);
    buttons->resize(this->width()*0.7 , this->height() * 0.1);

    imageView->resize(this->width()*0.7 , this->height() * 0.8);
    imageView->move(10, this->height() * 0.1);

    right->resize(this->width()* 0.3 - 10, this->height()* 0.9);
    right->move(this->width()* 0.7 + 10, 15);

    imageView->SetImage(myImage->Image());
}

void MainWindow::authorClickedSlot(){ qDebug() << "MainWindow::signal 'authorClicked' is not behandelt..."; }
void MainWindow::aboutClickedSlot() { qDebug() << "MainWindow::signal 'aboutClicked' is not behandelt...";  }
void MainWindow::loadClickedSlot()  { qDebug() << "MainWindow::signal 'loadClicked' is not behandelt...";   }
void MainWindow::saveClickedSlot()  { qDebug() << "MainWindow::signal 'saveClicked' is not behandelt...";   }
void MainWindow::updateImage()
{
    imageView->SetImage(myImage->Image());
    qDebug() << "MainWindow::updateImage()\timage updated";
}


MainWindow::~MainWindow()
{
    delete ui;
    delete buttons;
    delete imageView;
    delete mainLayout;
    delete leftLayout;
    delete right;
}

