#ifndef BRIGHTNESSS_H
#define BRIGHTNESSS_H


#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QWidget>
#include <QtDebug>



class BrightnessS : public QWidget
{
    Q_OBJECT
private:
    QPushButton* log;
    QPushButton* power;
    QPushButton* parts;

    QHBoxLayout* mainLayout;
    QVBoxLayout* buttonGroup;

    QSlider* slider;

signals:
    void logClicked();
    void PowerClicked();
    void PartsClicked();

public slots:
    void logClickedSlot();
    void PowerClickedSlot();
    void PartsClickedSlot();

public:
    ~BrightnessS();
    BrightnessS();
};

#endif // BRIGHTNESSS_H
