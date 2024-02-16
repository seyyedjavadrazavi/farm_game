#include "result.h"
#include "ui_result.h"

#include <QMessageBox>
#include<qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QTableView>
#include <QDataWidgetMapper>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QFile>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <cmath>
#include <string.h>

result::result(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::result)
{
    ui->setupUi(this);

    initDB();

    QSqlQuery qrry;
    qrry.exec("SELECT * FROM game_users ORDER BY user_farmId DESC");


    if (qrry.isActive())
    {
        while(qrry.next())
        {
            ui -> lbl_winners -> setText(ui -> lbl_winners -> text() + "\n" + qrry.value(0).toString() + " -> Score = " + qrry.value(6).toString());
        }
    }
}

result::~result()
{
    delete ui;
}

void result::initDB()
{
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../uni_game.db");
    if(!db.open())
        QMessageBox::warning(nullptr,"Database","Could not connect to database");
}
