#include "HyoNumberPad.h"
#include "ui_HyoNumberPad.h"

#include <QKeyEvent>

HyoNumberPad::HyoNumberPad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HyoNumberPad)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    connect(ui->toolButton_0, SIGNAL(clicked()), this, SLOT(onNumerClicked0()));
    connect(ui->toolButton_1, SIGNAL(clicked()), this, SLOT(onNumerClicked1()));
    connect(ui->toolButton_2, SIGNAL(clicked()), this, SLOT(onNumerClicked2()));
    connect(ui->toolButton_3, SIGNAL(clicked()), this, SLOT(onNumerClicked3()));
    connect(ui->toolButton_4, SIGNAL(clicked()), this, SLOT(onNumerClicked4()));
    connect(ui->toolButton_5, SIGNAL(clicked()), this, SLOT(onNumerClicked5()));
    connect(ui->toolButton_6, SIGNAL(clicked()), this, SLOT(onNumerClicked6()));
    connect(ui->toolButton_7, SIGNAL(clicked()), this, SLOT(onNumerClicked7()));
    connect(ui->toolButton_8, SIGNAL(clicked()), this, SLOT(onNumerClicked8()));
    connect(ui->toolButton_9, SIGNAL(clicked()), this, SLOT(onNumerClicked9()));
    connect(ui->toolButton_Minus, SIGNAL(clicked()), this, SLOT(onMinusClicked()));
    connect(ui->toolButton_Point, SIGNAL(clicked()), this, SLOT(onPointClicked()));

    connect(ui->toolButton_Enter, SIGNAL(clicked()), this, SLOT(onEnterClicked()));
    connect(ui->toolButton_Cancel, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
    connect(ui->toolButton_Clear, SIGNAL(clicked()), this, SLOT(onClearClicked()));
    connect(ui->toolButton_Delete, SIGNAL(clicked()), this, SLOT(onDeleteClicked()));
    connect(ui->toolButton_Backspace, SIGNAL(clicked()), this, SLOT(onBackspaceClicked()));
    connect(ui->toolButton_Left, SIGNAL(clicked()), this, SLOT(onLeftClicked()));
    connect(ui->toolButton_Right, SIGNAL(clicked()), this, SLOT(onRightClicked()));
}

HyoNumberPad::~HyoNumberPad()
{
    delete ui;
}

void HyoNumberPad::show(const QVariant &value)
{
    QDialog::show();

    m_dataType = value.type();

    ui->lineEdit->setText(value.toString());
    ui->lineEdit->selectAll();
    ui->lineEdit->setFocus();
}

void HyoNumberPad::pressKey(int val)
{
    QKeyEvent key(QEvent::KeyPress, val, Qt::NoModifier, QString(QChar(val)));
    QApplication::sendEvent(ui->lineEdit, &key);
}

void HyoNumberPad::onNumerClicked0()
{
    pressKey(Qt::Key_0);
}

void HyoNumberPad::onNumerClicked1()
{
    pressKey(Qt::Key_1);
}

void HyoNumberPad::onNumerClicked2()
{
    pressKey(Qt::Key_2);
}

void HyoNumberPad::onNumerClicked3()
{
    pressKey(Qt::Key_3);
}

void HyoNumberPad::onNumerClicked4()
{
    pressKey(Qt::Key_4);
}

void HyoNumberPad::onNumerClicked5()
{
    pressKey(Qt::Key_5);
}

void HyoNumberPad::onNumerClicked6()
{
    pressKey(Qt::Key_6);
}

void HyoNumberPad::onNumerClicked7()
{
    pressKey(Qt::Key_7);
}

void HyoNumberPad::onNumerClicked8()
{
    pressKey(Qt::Key_8);
}

void HyoNumberPad::onNumerClicked9()
{
    pressKey(Qt::Key_9);
}

void HyoNumberPad::onMinusClicked()
{
    QString text = ui->lineEdit->text();

    if( text.size() == 0 ) {
        text.prepend('-');
    } else if( text.at(0) != '-' ) {
        text.prepend('-');
    }

    ui->lineEdit->setText(text);
}

void HyoNumberPad::onPointClicked()
{
    QString text = ui->lineEdit->text();

    if( !text.contains('.') && text.size() > 0 && !(text.size() == 1 && text.at(0) == '-' ) ) {
        pressKey(Qt::Key_Period);
    }
}

void HyoNumberPad::onEnterClicked()
{
    QString text = ui->lineEdit->text();
    QVariant value;

    switch( m_dataType )
    {
    case QVariant::Int:               value.setValue(text.toInt()); break;
    case QVariant::UInt:             value.setValue(text.toUInt()); break;
    case QVariant::LongLong:     value.setValue(text.toLongLong()); break;
    case QVariant::ULongLong:   value.setValue(text.toULongLong()); break;
    case QVariant::Double:         value.setValue(text.toDouble()); break;
    default:                               value.setValue(text.toInt());
    }

    emit entered(value);

    this->close();
}

void HyoNumberPad::onCancelClicked()
{
    emit canceled();

    this->close();
}

void HyoNumberPad::onClearClicked()
{
    ui->lineEdit->clear();
}

void HyoNumberPad::onDeleteClicked()
{
    pressKey(Qt::Key_Delete);
}

void HyoNumberPad::onBackspaceClicked()
{
    pressKey(Qt::Key_Backspace);
}

void HyoNumberPad::onLeftClicked()
{
    pressKey(Qt::Key_Left);
}

void HyoNumberPad::onRightClicked()
{
    pressKey(Qt::Key_Right);
}
