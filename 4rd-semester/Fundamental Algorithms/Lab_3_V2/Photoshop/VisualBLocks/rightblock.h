#ifndef RIGHTBLOCK_H
#define RIGHTBLOCK_H

#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QString>

#include "VisualBLocks/brightnessblock.h"
#include "VisualBLocks/otherblock.h"
#include "VisualBLocks/rgbblock.h"


class RightBlock : public QWidget
{
    Q_OBJECT
private:
    BrightnessBlock* brightness;
    RgbBlock* rgb;
    OtherBlock* other;
    QComboBox* comboBox;

    QVBoxLayout* mainLayout;

signals:

    void LogClickedSignal();
    void PowerClickedSignal();
    void PartsClickedSignal();

    void RedSliderChangedSignal(int);
    void GreenSliderChangedSignal(int);
    void BlueSliderChangedSignal(int);

    void InverseClickedSignal();
    void WBClickedSignal();
    void BeautifyClickedSignal();

public:
    RightBlock(QWidget* parent);

public slots:
    void paintEvent(QPaintEvent *event);
    void ComboBoxChanged(QString);

    void LogClicked  ();
    void PowerClicked();
    void PartsClicked();

    void RedSliderChanged  (int);
    void GreenSliderChanged(int);
    void BlueSliderChanged (int);

    void InverseClicked ();
    void WBClicked      ();
    void BeautifyClicked();

};

#endif // RIGHTBLOCK_H
