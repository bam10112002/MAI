#ifndef THRESHOLDBLOCK_H
#define THRESHOLDBLOCK_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>

class ThresholdBlock: public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout* mainLayout;
    QVBoxLayout* blackLayout;
    QVBoxLayout* whiteLayout;

    QSpacerItem* spacer;

    QSlider* black;
    QSlider* white;

    QLabel* blackCircle;
    QLabel* whiteCircle;

public slots:
    void blackSliderChanged(int);
    void whiteSliderChanged(int);

public:
    ThresholdBlock();

signals:
     void blackChanged(int);
     void whiteChanged(int);
};



#endif // THRESHOLDBLOCK_H
