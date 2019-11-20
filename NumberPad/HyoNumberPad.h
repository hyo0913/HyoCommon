#ifndef HYONUMBERPAD_H
#define HYONUMBERPAD_H

#include <QDialog>

namespace Ui {
class HyoNumberPad;
}

class HyoNumberPad : public QDialog
{
    Q_OBJECT
    
public:
    explicit HyoNumberPad(QWidget *parent = 0);
    ~HyoNumberPad();
    
    void show(int value);

private:
    Ui::HyoNumberPad *ui;

    void appendNum(int val);

private slots:
    void onNumerClicked0();
    void onNumerClicked1();
    void onNumerClicked2();
    void onNumerClicked3();
    void onNumerClicked4();
    void onNumerClicked5();
    void onNumerClicked6();
    void onNumerClicked7();
    void onNumerClicked8();
    void onNumerClicked9();

    void onEnterClicked();
    void onCancelClicked();
    void onClearClicked();
    void onDeleteClicked();

signals:
    void entered(int);
};

#endif // HYONUMBERPAD_H
