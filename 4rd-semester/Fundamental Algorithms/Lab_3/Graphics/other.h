#ifndef OTHER_H
#define OTHER_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>

class Other : public QWidget
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
    Other();
    ~Other();
};

#endif // OTHER_H
