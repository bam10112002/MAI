#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1300, 700);

    mainLayout  = new QHBoxLayout(this);

    leftLayout  = new QVBoxLayout(this);
    leftLayout->setSpacing(10);
    rightLayout = new QVBoxLayout(this);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

//Left Block
    // Buttons
    buttonLayout = new QHBoxLayout(this);
    about  = new QPushButton(this);
    author = new QPushButton(this);
    reload = new QPushButton(this);
    save   = new QPushButton(this);
    buttonLayout->setAlignment(Qt::AlignLeft);
    buttonLayout->addWidget(about);

    about->setText("About program");
    connect(about, SIGNAL(clicked()), this, SLOT(ShowAboutDialog()));
    about->setFixedSize(this->width() * 0.1, about->height());

    buttonLayout->addWidget(author);
    author->setText("Author");
    author->setFixedSize(this->width() * 0.1, author->height());

    reload->setFixedSize(this->width() * 0.1, about->height());
    reload->setText("Reload");
    buttonLayout->addWidget(reload);

    buttonLayout->addWidget(save);
    save->setFixedSize(this->width() * 0.1, save->height());
    save->setText("Save");

    // Image
    labelLayout= new QHBoxLayout(this);
    imageView = new ImageView(this, this->width() * 0.7, this->height() * 0.9);
    image = new QLabel(this);

//    image->setFixedSize(this->width() * 0.7, this->height() * 0.9);
//    image->setStyleSheet("background: black;");
    img = new MyImage(image, this);
    imageView->SetImage(img->getImg());
//    imageView->SetImage(img->getImg());

//    image->setPixmap(QPixmap::fromImage(img->getImg()));
//    labelLayout->addWidget(image);
    labelLayout->addWidget(imageView);

    // Add
    leftLayout->addLayout(buttonLayout);
    leftLayout->addLayout(labelLayout);


//Right Block
    filters = new QComboBox(this);
    filters->addItem("RGB");
    filters->addItem("Threshold");
    filters->addItem("Other");
    filters->addItem("Brightness");
    connect(filters, SIGNAL(currentTextChanged(QString)), this, SLOT(ComboBoxChange(QString)));


    RgbBlocS = new RgbBlock();
    connect(RgbBlocS, SIGNAL(redChanged(int)), this, SLOT(RedSliderChanged(int)));
    connect(RgbBlocS, SIGNAL(greenChanged(int)), this, SLOT(GreenSliderChanged(int)));
    connect(RgbBlocS, SIGNAL(blueChanged(int)), this, SLOT(BlueSliderChanged(int)));

    ThrBlockS = new ThresholdBlock();
    connect(ThrBlockS, SIGNAL(blackChanged(int)), this, SLOT(BottomLimitChanged(int)));
    connect(ThrBlockS, SIGNAL(whiteChanged(int)), this, SLOT(UpLimitChanged(int)));

    otherS = new Other();
    connect(otherS, SIGNAL(beautifyClicked()), this, SLOT(BeautifySlot()));
    connect(otherS, SIGNAL(inverseClicked()), this, SLOT(InverseSlot()));
    connect(otherS, SIGNAL(wbClicked()), this, SLOT(WhiteBlackSlot()));

    brightnessS = new BrightnessS();
    connect(brightnessS, SIGNAL(logClicked()), this, SLOT(LogSlot()));
    connect(brightnessS, SIGNAL(PowerClicked()), this, SLOT(PowerSlot()));
    connect(brightnessS, SIGNAL(PartsClicked()), this, SLOT(PartsSlot()));

    rightLayout->addWidget(filters);
    rightLayout->addWidget(RgbBlocS);
    rightLayout->addWidget(ThrBlockS);
    rightLayout->addWidget(otherS);
    rightLayout->addWidget(brightnessS);

    otherS->hide();
    ThrBlockS->hide();
    brightnessS->hide();

    ui->centralwidget->setLayout(mainLayout);
}

void MainWindow::ShowAboutDialog()
{
    QMessageBox* mes = new QMessageBox();
    mes->setWindowTitle("Об автре");
    mes->setText("Группа: М80-210б-20\nСтудент: Буловятов А.М.");
    mes->show();
}
void MainWindow::ShowAuthorDialog()
{

}

void MainWindow::ComboBoxChange(QString text)
{
    if (text == "RGB")
    {
        RgbBlocS->show();
        ThrBlockS->hide();
        otherS->hide();
        brightnessS->hide();
    }
    else if (text == "Threshold")
    {
        ThrBlockS->show();
        RgbBlocS->hide();
        otherS->hide();
        brightnessS->hide();

    }
    else if (text == "Other")
    {
            otherS->show();
            RgbBlocS->hide();
            ThrBlockS->hide();
            brightnessS->hide();
    }
    else if (text == "Brightness")
    {
        brightnessS->show();
        otherS->hide();
        RgbBlocS->hide();
        ThrBlockS->hide();
    }
    this->update();
//        his->repa
//        Filler->setStyleSheet("border: 2px solid blue;");
}

void MainWindow::RedSliderChanged(int val)
{
    img->rgb.SetRed(val);
    image->setPixmap(QPixmap::fromImage(img->getImg()));
}
void MainWindow::GreenSliderChanged(int val)
{
    img->rgb.SetGreen(val);
    image->setPixmap(QPixmap::fromImage(img->getImg()));
}
void MainWindow::BlueSliderChanged(int val)
{
    img->rgb.SetBlue(val);
    image->setPixmap(QPixmap::fromImage(img->getImg()));
}

void MainWindow::UpLimitChanged(int val)
{
    img->threshold.setUp(val);
    image->setPixmap(QPixmap::fromImage(img->getImg()));
}
void MainWindow::BottomLimitChanged(int val)
{
    img->threshold.setBottom(val);
    image->setPixmap(QPixmap::fromImage(img->getImg()));
}

void MainWindow::InverseSlot()
{
    img->Inverse();
    image->setPixmap(QPixmap::fromImage(img->getImg()));
}
void MainWindow::WhiteBlackSlot()
{
    img->ToBlackWhite();
    image->setPixmap(QPixmap::fromImage(img->getImg()));
}
void MainWindow::BeautifySlot()
{
    img->Best();
    image->setPixmap(QPixmap::fromImage(img->getImg()));
}

void MainWindow::LogSlot()
{
    img->brightness.Log();
    image->setPixmap(QPixmap::fromImage(img->getImg()));
}
void MainWindow::PowerSlot()
{
    qDebug() << "MainWindow::PowerSlot()";
    img->brightness.Power();
    image->setPixmap(QPixmap::fromImage(img->getImg()));
}
void MainWindow::PartsSlot()
{

}


MainWindow::~MainWindow()
{
    delete ui;
}

