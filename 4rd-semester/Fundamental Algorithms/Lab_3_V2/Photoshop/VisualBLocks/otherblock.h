#ifndef OTHERBLOCK_H
#define OTHERBLOCK_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>

class OtherBlock : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout* mainLayout;
    QPushButton* inverse;
    QPushButton* whiteBlack;
    QPushButton* beautify;

signals:
    void inverseClicked();
    void wbClicked();
    void beautifyClicked();

public slots:
    void inverseClickedSlot();
    void wbClickedSlot();
    void beautifyClickedSlot();

public:
    OtherBlock();
    ~OtherBlock();
};

#endif // OTHERBLOCK_H
