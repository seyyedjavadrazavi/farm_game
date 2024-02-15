#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "number_of_players.h"
#include "scene.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QTableView>
#include <QDataWidgetMapper>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this -> setStyleSheet("background-color: rgb(9, 165, 159);");
    initDB();

    QSqlQueryModel *model = new QSqlQueryModel;
    QString query = "SELECT * FROM game_users";
    model->setQuery(query);

    if (model -> rowCount() > 0)
    {
        ui -> btn_start -> hide();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::new_game()
{
    number_of_players *w = new number_of_players("1");
    w->show();
    this->hide();
}

void MainWindow::resume()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QString query = "SELECT  * FROM game_users";

    model->setQuery(query);

    QList<QString> usr_names;
    for(int j=0; j<model->rowCount(); j++)
    {
        QString name = model->data(model->index(j, 0)).toString();
        usr_names.append(name);
    }

    scene *scenes = new scene(model->rowCount(), usr_names);
//    scenes -> resize(500, 500);
    scenes -> show();
}

void MainWindow::initDB()
{
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Seyyed Javad Razavi/Desktop/game/uni_game.db");
    if(!db.open())
        QMessageBox::warning(nullptr,"Database","Could not connect to database");
}
