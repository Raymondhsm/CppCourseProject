#include "exit.h"
#include "ui_exit.h"
#include <QApplication>

Exit::Exit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Exit)
{
    ui->setupUi(this);

}

Exit::~Exit()
{
    delete ui;
}

void Exit::on_buttonBox_accepted()
{

}

void Exit::on_buttonBox_rejected()
{
    this->close();
}
