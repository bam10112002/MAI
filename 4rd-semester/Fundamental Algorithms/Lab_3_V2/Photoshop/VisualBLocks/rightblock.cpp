#include "rightblock.h"

RightBlock::RightBlock(QWidget* parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout();

    comboBox = new QComboBox(this);

    comboBox->addItem("RGB");
    comboBox->addItem("Threshold");
    comboBox->addItem("Other");
    comboBox->addItem("Brightness");

    connect(comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(ComboBoxChanged(QString)));


    rgb = new RgbBlock();
    connect(rgb, SIGNAL(redChanged(int)),   this, SLOT(RedSliderChanged(int))  );
    connect(rgb, SIGNAL(greenChanged(int)), this, SLOT(GreenSliderChanged(int)));
    connect(rgb, SIGNAL(blueChanged(int)),  this, SLOT(BlueSliderChanged(int)) );


    other = new OtherBlock();
    connect(other, SIGNAL(inverseClicked()), this, SLOT(InverseClicked()));
    connect(other, SIGNAL(wbClicked()),      this, SLOT(WBClicked()));
    connect(other, SIGNAL(beautifyClicked()),this, SLOT(BeautifyClicked()));


    brightness = new BrightnessBlock();
    connect(brightness, SIGNAL(logClicked()),   this, SLOT(LogClicked()));
    connect(brightness, SIGNAL(PowerClicked()), this, SLOT(PowerClicked()));
    connect(brightness, SIGNAL(PartsClicked()), this, SLOT(PartsClicked()));

    mainLayout->addWidget(comboBox);
    mainLayout->addWidget(rgb);
    mainLayout->addWidget(other);
    mainLayout->addWidget(brightness);

//    rgb->hide();
    other->hide();
    brightness->hide();

    this->setLayout(mainLayout);
}

void RightBlock::ComboBoxChanged(QString text)
{
    if (text == "RGB")
    {
        rgb->show();
        other->hide();
        brightness->hide();
    }
    else if (text == "Threshold")
    {
        rgb->hide();
        other->hide();
        brightness->hide();

    }
    else if (text == "Other")
    {
        other->show();
        rgb->hide();
        brightness->hide();
    }
    else if (text == "Brightness")
    {
        brightness->show();
        other->hide();
        rgb->hide();
    }
    this->update();
}

void RightBlock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED (event);
    resize(this->width(),this->height());
}

void RightBlock::RedSliderChanged(int delta)  { emit RedSliderChangedSignal(delta);   }
void RightBlock::GreenSliderChanged(int delta){ emit GreenSliderChangedSignal(delta); }
void RightBlock::BlueSliderChanged(int delta) { emit BlueSliderChangedSignal(delta);  }

void RightBlock::InverseClicked() { emit InverseClickedSignal();  }
void RightBlock::WBClicked()      { emit WBClickedSignal();       }
void RightBlock::BeautifyClicked(){ emit BeautifyClickedSignal(); }

void RightBlock::LogClicked()  { emit LogClickedSignal();   }
void RightBlock::PowerClicked(){ emit PowerClickedSignal(); }
void RightBlock::PartsClicked(){ emit PartsClickedSignal(); }
