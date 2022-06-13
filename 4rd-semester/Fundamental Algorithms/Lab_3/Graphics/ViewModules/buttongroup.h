#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

class ButtonGroup : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout* mainLayout;
    QPushButton* author;
    QPushButton* about;
    QPushButton* load;
    QPushButton* save;

public:
    ButtonGroup(QWidget* parent);
    ~ButtonGroup();
};

#endif // BUTTONGROUP_H
