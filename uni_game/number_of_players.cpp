#include "number_of_players.h"
#include "ui_number_of_players.h"
#include "login.h"

#include<qdebug.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <qmessagebox.h>


number_of_players::number_of_players(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::number_of_players)
{
    ui->setupUi(this);
}

number_of_players::number_of_players(QString tt):
    QDialog(nullptr),
    ui(new Ui::number_of_players)
{
    ui->setupUi(this);
    this -> setStyleSheet("background-color: rgb(9, 165, 159);");
}


number_of_players::~number_of_players()
{
    delete ui;
}

int number_of_players::numberOfUsers()
{
    if(ui->NoPlayers->value() == 0)
    {
        QMessageBox::warning(this,"خطا","تعداد بازیکنان باید بیشتر از صفر باشد");
    }
    else{
        int no_palyers = ui -> NoPlayers->value();
        Login *log = new Login(no_palyers);
        log->show();

        this->hide();

    }
}

