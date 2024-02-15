#include "sence.h"
#include "ui_sence.h"

sence::sence(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sence)
{
    ui->setupUi(this);
}

sence::~sence()
{
    delete ui;
}
