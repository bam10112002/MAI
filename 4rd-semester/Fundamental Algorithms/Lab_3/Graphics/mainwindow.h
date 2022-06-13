#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include <QComboBox>
#include <QSlider>
#include <QtDebug>
#include "myimage.h"
#include "rgbblock.h"
#include "thresholdblock.h"
#include "other.h"
#include "brightnesss.h"
#include "ViewModules/imageview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    QHBoxLayout* mainLayout;

    QVBoxLayout* leftLayout;
    QVBoxLayout* rightLayout;

    // Блок кнопок
    QHBoxLayout* buttonLayout;
    QPushButton* about;
    QPushButton* author;
    QPushButton* reload;
    QPushButton* save;

    // Изображение
    QHBoxLayout* labelLayout;
    QLabel* image;
    ImageView* imageView;


// Right
    QComboBox* filters;
    RgbBlock* RgbBlocS;
    ThresholdBlock* ThrBlockS;
    Other* otherS;
    BrightnessS* brightnessS;

    // Вспомогательные
    MyImage* img;
    Ui::MainWindow *ui;

private slots:

    void ShowAboutDialog();
    void ShowAuthorDialog();
    void ComboBoxChange(QString text);

    void RedSliderChanged(int);
    void GreenSliderChanged(int);
    void BlueSliderChanged(int);

    void UpLimitChanged(int);
    void BottomLimitChanged(int);

    void InverseSlot();
    void WhiteBlackSlot();
    void BeautifySlot();

    void LogSlot();
    void PowerSlot();
    void PartsSlot();
};


#endif // MAINWINDOW_H
