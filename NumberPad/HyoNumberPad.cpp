#include "HyoNumberPad.h"
#include "ui_HyoNumberPad.h"

HyoNumberPad::HyoNumberPad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HyoNumberPad)
{
    ui->setupUi(this);

    //this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(onNumerClicked0()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(onNumerClicked1()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(onNumerClicked2()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(onNumerClicked3()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(onNumerClicked4()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(onNumerClicked5()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(onNumerClicked6()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(onNumerClicked7()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(onNumerClicked8()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(onNumerClicked9()));

    connect(ui->pushButton_Enter, SIGNAL(clicked()), this, SLOT(onEnterClicked()));
    connect(ui->pushButton_Cancel, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
    connect(ui->pushButton_Clear, SIGNAL(clicked()), this, SLOT(onClearClicked()));
    connect(ui->pushButton_Delete, SIGNAL(clicked()), this, SLOT(onDeleteClicked()));
}

HyoNumberPad::~HyoNumberPad()
{
    delete ui;
}

void HyoNumberPad::show(int value)
{
    ui->spinBoxValue->setValue(value);

    QDialog::show();
}

void HyoNumberPad::appendNum(int val)
{
    int value = ui->spinBoxValue->value()*10+val;

    ui->spinBoxValue->setValue(value);
}

void HyoNumberPad::onNumerClicked0()
{
    appendNum(0);
}

void HyoNumberPad::onNumerClicked1()
{
    appendNum(1);
}

void HyoNumberPad::onNumerClicked2()
{
    appendNum(2);
}

void HyoNumberPad::onNumerClicked3()
{
    appendNum(3);
}

void HyoNumberPad::onNumerClicked4()
{
    appendNum(4);
}

void HyoNumberPad::onNumerClicked5()
{
    appendNum(5);
}

void HyoNumberPad::onNumerClicked6()
{
    appendNum(6);
}

void HyoNumberPad::onNumerClicked7()
{
    appendNum(7);
}

void HyoNumberPad::onNumerClicked8()
{
    appendNum(8);
}

void HyoNumberPad::onNumerClicked9()
{
    appendNum(9);
}

void HyoNumberPad::onEnterClicked()
{
    emit entered(ui->spinBoxValue->value());

    this->close();
}

void HyoNumberPad::onCancelClicked()
{
    this->close();
}

void HyoNumberPad::onClearClicked()
{
    ui->spinBoxValue->setValue(0);
}

void HyoNumberPad::onDeleteClicked()
{
    int value = ui->spinBoxValue->value()/10;

    ui->spinBoxValue->setValue(value);
}
