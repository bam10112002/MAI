#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QPaintEvent>
#include "VisualBLocks/imageview.h"
#include "VisualBLocks/buttongroup.h"
#include "VisualBLocks/rightblock.h"
#include "Filters/myimage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    // отображение
    ButtonGroup* buttons;
    ImageView* imageView;
    RightBlock* right;
    QVBoxLayout* leftLayout;
    QHBoxLayout* mainLayout;

    // Логика
    MyImage* myImage;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void paintEvent(QPaintEvent *event);
    void authorClickedSlot();
    void aboutClickedSlot();
    void loadClickedSlot();
    void saveClickedSlot();
    void updateImage();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
