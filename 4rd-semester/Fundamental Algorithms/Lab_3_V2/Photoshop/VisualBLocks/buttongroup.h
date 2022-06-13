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

private: signals:
    void authorClicked();
    void aboutClicked();
    void loadClicked();
    void saveClicked();

public slots:
    void authorClickedSlot();
    void aboutClickedSlot();
    void loadClickedSlot();
    void saveClickedSlot();
};

#endif // BUTTONGROUP_H
