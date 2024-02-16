#include "scene.h"
#include "ui_scene.h"
#include "result.h"

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
#include <QAudioOutput>

scene::scene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::scene)
{
    ui->setupUi(this);
}

scene::~scene()
{
    delete ui;
}

scene::scene(int number_of_players, QList<QString> user_name_lst) :
    QMainWindow(nullptr),
    ui(new Ui::scene)
{
    ui->setupUi(this);

    QPixmap bkgnd("icons/scene.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    QTimer *timer = new QTimer;
    timer->setInterval(1000);

    connect(timer , SIGNAL(timeout()) , this , SLOT(timerTick1()));
    timer->start();

    buttons_stup();
    remaining_players = number_of_players;
    user_name = user_name_lst[0];
    user_name_lst.removeFirst();
    user_names_lst = user_name_lst;

    ui -> lbl_plyer_name -> setText("Player Name : " + user_name);

    initDB();
}

int scene::rd_btn_slction()
{
    int choice = -1;
    if (ui -> rd_btn_none ->isChecked())
    {
        choice = 1;
    }
    else if (ui -> rd_btn_cow ->isChecked())
    {
        choice = 2;
    }
    else if (ui -> rd_btn_hen ->isChecked())
    {
        choice = 3;
    }
    else if (ui -> rd_btn_shep ->isChecked())
    {
        choice = 4;
    }
    else if (ui -> rd_btn_grain ->isChecked())
    {
        choice = 5;
    }
    else if (ui -> rd_btn_wheat ->isChecked())
    {
        choice = 6;
    }
    else if (ui -> rd_btn_wrkr ->isChecked())
    {
        choice = 7;
    }
    else if (ui -> rd_btn_kill ->isChecked())
    {
        choice = 8;
    }

    return choice;
}

void scene::select_bttn(QPushButton *button, int i, int j)
{
    if (boarder[i][j] == 0)
    {
        boarder[i][j] = 1;
        coins = coins - 3;
        ui -> lbl_coins->setText("Coins: " + QString::number(coins));

        button -> setStyleSheet(QString("QPushButton { background-color: green; }"));
    }
    else if (boarder[i][j] == 1)
    {
        if (rd_btn_slction() == 2)
        {
            boarder[i][j] = 2;
            coins -= 7;
            ui -> lbl_coins->setText("Coins: " + QString::number(coins));
            button -> setStyleSheet("border-image:url(icons/cow.png);");

            m_player = new QMediaPlayer();
            m_player -> setMedia(QUrl("icons/cow.mp3"));
            m_player -> play();
        }
        else if (rd_btn_slction() == 3)
        {
            boarder[i][j] = 3;
            coins -= 3;
            ui -> lbl_coins->setText("Coins: " + QString::number(coins));
            button -> setStyleSheet("border-image:url(icons/hen.png);");

            m_player = new QMediaPlayer();
            m_player -> setMedia(QUrl("icons/hen.mp3"));
            m_player -> play();
        }
        else if (rd_btn_slction() == 4)
        {
            boarder[i][j] = 4;
            coins -= 5;
            ui -> lbl_coins->setText("Coins: " + QString::number(coins));
            button -> setStyleSheet("border-image:url(icons/shep.png);");

            m_player = new QMediaPlayer();
            m_player -> setMedia(QUrl("icons/sheep.mp3"));
            m_player -> play();
        }
        else if (rd_btn_slction() == 5)
        {
            boarder[i][j] = 5;
            coins -= 2;
            ui -> lbl_coins->setText("Coins: " + QString::number(coins));
            button -> setStyleSheet("border-image:url(icons/jo.jpeg);");
        }
        else if (rd_btn_slction() == 6)
        {
            boarder[i][j] = 6;
            coins -= 2;
            ui -> lbl_coins->setText("Coins: " + QString::number(coins));
            button -> setStyleSheet("border-image:url(icons/wheat.jpeg);");
        }
        else if (rd_btn_slction() == 7)
        {

        }
    }
    else if (boarder[i][j] == 2)
    {
        if(rd_btn_slction() == 7)
        {
            if (workers != 0)
            {
                workers -= 1;
                ui -> lbl_no_wrkrs -> setText("No. of Workers: " + QString::number(workers));
                button -> setStyleSheet(QString("background-color: rgb(57, 183, 208);"));

                QTimer *timer = new QTimer;
                timer->setInterval(1000);
                connect(timer, &QTimer::timeout, [=](){ this->product_timer(timer, button, "milk_cow"); });
                timer->start();
                button ->setProperty("remainingTime", 20);
                button -> setProperty("product", "milk_cow");
                boarder[i][j] = 8;
            }
        }
        else if(rd_btn_slction() == 8)
        {
            button -> setStyleSheet(QString("QPushButton { background-color: white; }"));
            button -> setProperty("product", " ");
            boarder[i][j] = 0;
            coins += 7;
            ui -> lbl_coins -> setText("Coins: " + QString::number(coins));
         }
    }
    else if (boarder[i][j] == 3)
    {
        if(rd_btn_slction() == 7)
        {
            if (workers != 0)
            {
                workers -= 1;
                ui -> lbl_no_wrkrs -> setText("No. of Workers: " + QString::number(workers));
                button -> setStyleSheet(QString("background-color: rgb(57, 183, 208);"));

                QTimer *timer = new QTimer;
                timer->setInterval(1000);
                connect(timer, &QTimer::timeout, [=](){ this->product_timer(timer, button, "egg"); });
                timer->start();
                button ->setProperty("remainingTime", 15);
                button -> setProperty("product", "egg");
                boarder[i][j] = 8;
            }
        }
        else if(rd_btn_slction() == 8)
        {
            button -> setStyleSheet(QString("QPushButton { background-color: white; }"));
            button -> setProperty("product", " ");
            boarder[i][j] = 0;
            coins += 3;
            ui -> lbl_coins -> setText("Coins: " + QString::number(coins));
        }
    }
    else if (boarder[i][j] == 4)
    {
        if(rd_btn_slction() == 7)
        {
            if (workers != 0)
            {
                workers -= 1;
                ui -> lbl_no_wrkrs -> setText("No. of Workers: " + QString::number(workers));
                button -> setStyleSheet(QString("background-color: rgb(57, 183, 208);"));

                QTimer *timer = new QTimer;
                timer->setInterval(1000);
                connect(timer, &QTimer::timeout, [=](){ this->product_timer(timer, button, "milk_shep"); });
                timer->start();
                button ->setProperty("remainingTime", 20);
                button -> setProperty("product", "milk_shep");
                boarder[i][j] = 8;
            }
        }
        else if(rd_btn_slction() == 8)
        {
            button -> setStyleSheet(QString("QPushButton { background-color: white; }"));
            button -> setProperty("product", " ");
            boarder[i][j] = 0;
            coins += 5;
            ui -> lbl_coins -> setText("Coins: " + QString::number(coins));
        }
    }
    else if (boarder[i][j] == 5)
    {
        if(rd_btn_slction() == 7)
        {
            if (workers != 0)
            {
                workers -= 1;
                ui -> lbl_no_wrkrs -> setText("No. of Workers: " + QString::number(workers));
                button -> setStyleSheet(QString("background-color: rgb(57, 183, 208);"));

                QTimer *timer = new QTimer;
                timer->setInterval(1000);
                connect(timer, &QTimer::timeout, [=](){ this->product_timer(timer, button, "grain_flour"); });
                timer->start();
                button ->setProperty("remainingTime", 20);
                button -> setProperty("product", "grain_flour");
                boarder[i][j] = 8;
            }
        }
    }
    else if (boarder[i][j] == 6)
    {
        if(rd_btn_slction() == 7)
        {
            if (workers != 0)
            {
                workers -= 1;
                ui -> lbl_no_wrkrs -> setText("No. of Workers: " + QString::number(workers));
                button -> setStyleSheet(QString("background-color: rgb(57, 183, 208);"));

                QTimer *timer = new QTimer;
                timer->setInterval(1000);
                connect(timer, &QTimer::timeout, [=](){ this->product_timer(timer, button, "flour"); });
                timer->start();
                button ->setProperty("remainingTime", 25);
                button -> setProperty("product", "flour");
                boarder[i][j] = 8;
            }
        }
    }
    else if (boarder[i][j] == 7) // kill a cow, shep or henn
    {

    }
    else if (boarder[i][j] == 8) // get the prize
    {
//        qDebug() << button->property("product");

        if(button -> property("remainingTime") <= 0)
        {
            if(button->property("product") == "milk_cow")
            {
                int rm_Time = button->property("remainingTime").toInt();
                rm_Time /= -3;
                int prize = 5;
                prize -= rm_Time;
                coins += prize;
                ui -> lbl_coins -> setText("Coins: " + QString::number(coins));
                boarder[i][j] = 2;
                button -> setStyleSheet("border-image:url(icons/cow.png);");
            }
            else if(button->property("product") == "milk_shep")
            {
                int rm_Time = button->property("remainingTime").toInt();
                rm_Time /= -4;
                int prize = 3;
                prize -= rm_Time;
                coins += prize;
                ui -> lbl_coins -> setText("Coins: " + QString::number(coins));
                boarder[i][j] = 4;
                button -> setStyleSheet("border-image:url(icons/shep.png);");
            }
            else if(button->property("product") == "egg")
            {
                int rm_Time = button->property("remainingTime").toInt();
                rm_Time /= -5;
                int prize = 3;
                prize -= rm_Time;
                coins += prize;
                ui -> lbl_coins -> setText("Coins: " + QString::number(coins));
                boarder[i][j] = 3;
                button -> setStyleSheet("border-image:url(icons/hen.png);");
            }
            else if(button->property("product") == "grain_flour")
            {
                int rm_Time = button->property("remainingTime").toInt();
                rm_Time /= -10;
                int prize = 2;
                prize -= rm_Time;
                coins += prize;
                ui -> lbl_coins -> setText("Coins: " + QString::number(coins));
                boarder[i][j] = 0;
//                button -> setStyleSheet("border-image:url(icons/jo.jpeg);");
                button -> setStyleSheet(QString("QPushButton { background-color: white; }"));
            }
            else if(button->property("product") == "flour")
            {
                int rm_Time = button->property("remainingTime").toInt();
                rm_Time /= -12;
                int prize = 3;
                prize -= rm_Time;
                coins += prize;
                ui -> lbl_coins -> setText("Coins: " + QString::number(coins));
                boarder[i][j] = 0;
//                button -> setStyleSheet("border-image:url(icons/wheat.jpeg);");
                button -> setStyleSheet(QString("QPushButton { background-color: white; }"));
            }

            workers += 1;
            ui -> lbl_no_wrkrs -> setText("No. of Workers:" + QString::number(workers));
            button -> setText("");
            button -> setProperty("product", " ");
        }
    }
}

void scene::buttons_stup()
{
    ui -> btn_1->setMinimumHeight(70);
    ui -> btn_1->setMinimumHeight(70);
    ui -> btn_2->setMinimumHeight(70);
    ui -> btn_2->setMinimumHeight(70);
    ui -> btn_3->setMinimumHeight(70);
    ui -> btn_3->setMinimumHeight(70);
    ui -> btn_4->setMinimumHeight(70);
    ui -> btn_4->setMinimumHeight(70);
    ui -> btn_5->setMinimumHeight(70);
    ui -> btn_5->setMinimumHeight(70);
    ui -> btn_6->setMinimumHeight(70);
    ui -> btn_6->setMinimumHeight(70);
    ui -> btn_7->setMinimumHeight(70);
    ui -> btn_7->setMinimumHeight(70);
    ui -> btn_8->setMinimumHeight(70);
    ui -> btn_8->setMinimumHeight(70);
    ui -> btn_9->setMinimumHeight(70);
    ui -> btn_9->setMinimumHeight(70);
    ui -> btn_10->setMinimumHeight(70);
    ui -> btn_10->setMinimumHeight(70);
    ui -> btn_11->setMinimumHeight(70);
    ui -> btn_11->setMinimumHeight(70);
    ui -> btn_12->setMinimumHeight(70);
    ui -> btn_12->setMinimumHeight(70);
    ui -> btn_13->setMinimumHeight(70);
    ui -> btn_13->setMinimumHeight(70);
    ui -> btn_14->setMinimumHeight(70);
    ui -> btn_14->setMinimumHeight(70);
    ui -> btn_15->setMinimumHeight(70);
    ui -> btn_15->setMinimumHeight(70);
    ui -> btn_16->setMinimumHeight(70);
    ui -> btn_16->setMinimumHeight(70);
    ui -> btn_17->setMinimumHeight(70);
    ui -> btn_17->setMinimumHeight(70);
    ui -> btn_18->setMinimumHeight(70);
    ui -> btn_18->setMinimumHeight(70);
    ui -> btn_19->setMinimumHeight(70);
    ui -> btn_19->setMinimumHeight(70);
    ui -> btn_20->setMinimumHeight(70);
    ui -> btn_20->setMinimumHeight(70);
    ui -> btn_21->setMinimumHeight(70);
    ui -> btn_21->setMinimumHeight(70);
    ui -> btn_22->setMinimumHeight(70);
    ui -> btn_22->setMinimumHeight(70);
    ui -> btn_23->setMinimumHeight(70);
    ui -> btn_23->setMinimumHeight(70);
    ui -> btn_24->setMinimumHeight(70);
    ui -> btn_24->setMinimumHeight(70);
    ui -> btn_25->setMinimumHeight(70);
    ui -> btn_25->setMinimumHeight(70);
    ui -> btn_25->setMinimumHeight(70);
    ui -> btn_26->setMinimumHeight(70);
    ui -> btn_26->setMinimumHeight(70);
    ui -> btn_27->setMinimumHeight(70);
    ui -> btn_27->setMinimumHeight(70);
    ui -> btn_28->setMinimumHeight(70);
    ui -> btn_28->setMinimumHeight(70);
    ui -> btn_29->setMinimumHeight(70);
    ui -> btn_29->setMinimumHeight(70);
    ui -> btn_30->setMinimumHeight(70);
    ui -> btn_30->setMinimumHeight(70);
    ui -> btn_31->setMinimumHeight(70);
    ui -> btn_31->setMinimumHeight(70);
    ui -> btn_32->setMinimumHeight(70);
    ui -> btn_32->setMinimumHeight(70);
    ui -> btn_33->setMinimumHeight(70);
    ui -> btn_33->setMinimumHeight(70);
    ui -> btn_34->setMinimumHeight(70);
    ui -> btn_34->setMinimumHeight(70);
    ui -> btn_35->setMinimumHeight(70);
    ui -> btn_35->setMinimumHeight(70);
    ui -> btn_36->setMinimumHeight(70);
    ui -> btn_36->setMinimumHeight(70);
    ui -> btn_37->setMinimumHeight(70);
    ui -> btn_37->setMinimumHeight(70);
    ui -> btn_38->setMinimumHeight(70);
    ui -> btn_38->setMinimumHeight(70);
    ui -> btn_39->setMinimumHeight(70);
    ui -> btn_39->setMinimumHeight(70);
    ui -> btn_40->setMinimumHeight(70);
    ui -> btn_40->setMinimumHeight(70);
    ui -> btn_41->setMinimumHeight(70);
    ui -> btn_41->setMinimumHeight(70);
    ui -> btn_42->setMinimumHeight(70);
    ui -> btn_42->setMinimumHeight(70);
    ui -> btn_43->setMinimumHeight(70);
    ui -> btn_43->setMinimumHeight(70);
    ui -> btn_44->setMinimumHeight(70);
    ui -> btn_44->setMinimumHeight(70);
    ui -> btn_45->setMinimumHeight(70);
    ui -> btn_45->setMinimumHeight(70);
    ui -> btn_46->setMinimumHeight(70);
    ui -> btn_46->setMinimumHeight(70);
    ui -> btn_47->setMinimumHeight(70);
    ui -> btn_47->setMinimumHeight(70);
    ui -> btn_48->setMinimumHeight(70);
    ui -> btn_48->setMinimumHeight(70);
    ui -> btn_49->setMinimumHeight(70);
    ui -> btn_49->setMinimumHeight(70);
    ui -> btn_50->setMinimumHeight(70);
    ui -> btn_50->setMinimumHeight(70);
    ui -> btn_51->setMinimumHeight(70);
    ui -> btn_51->setMinimumHeight(70);
    ui -> btn_52->setMinimumHeight(70);
    ui -> btn_52->setMinimumHeight(70);
    ui -> btn_53->setMinimumHeight(70);
    ui -> btn_53->setMinimumHeight(70);
    ui -> btn_54->setMinimumHeight(70);
    ui -> btn_54->setMinimumHeight(70);
    ui -> btn_55->setMinimumHeight(70);
    ui -> btn_55->setMinimumHeight(70);
    ui -> btn_56->setMinimumHeight(70);
    ui -> btn_56->setMinimumHeight(70);
    ui -> btn_57->setMinimumHeight(70);
    ui -> btn_57->setMinimumHeight(70);
    ui -> btn_58->setMinimumHeight(70);
    ui -> btn_58->setMinimumHeight(70);
    ui -> btn_59->setMinimumHeight(70);
    ui -> btn_59->setMinimumHeight(70);
    ui -> btn_60->setMinimumHeight(70);
    ui -> btn_60->setMinimumHeight(70);
    ui -> btn_61->setMinimumHeight(70);
    ui -> btn_61->setMinimumHeight(70);
    ui -> btn_62->setMinimumHeight(70);
    ui -> btn_62->setMinimumHeight(70);
    ui -> btn_63->setMinimumHeight(70);
    ui -> btn_63->setMinimumHeight(70);
    ui -> btn_64->setMinimumHeight(70);
    ui -> btn_64->setMinimumHeight(70);

    connect(ui -> btn_1, &QPushButton::clicked, [=](){ this->pushButtonClicked(1); });
    connect(ui -> btn_2, &QPushButton::clicked, [=](){ this->pushButtonClicked(2); });
    connect(ui -> btn_3, &QPushButton::clicked, [=](){ this->pushButtonClicked(3); });
    connect(ui -> btn_4, &QPushButton::clicked, [=](){ this->pushButtonClicked(4); });
    connect(ui -> btn_5, &QPushButton::clicked, [=](){ this->pushButtonClicked(5); });
    connect(ui -> btn_6, &QPushButton::clicked, [=](){ this->pushButtonClicked(6); });
    connect(ui -> btn_7, &QPushButton::clicked, [=](){ this->pushButtonClicked(7); });
    connect(ui -> btn_8, &QPushButton::clicked, [=](){ this->pushButtonClicked(8); });
    connect(ui -> btn_9, &QPushButton::clicked, [=](){ this->pushButtonClicked(9); });
    connect(ui -> btn_10, &QPushButton::clicked, [=](){ this-> pushButtonClicked(10); });
    connect(ui -> btn_11, &QPushButton::clicked, [=](){ this-> pushButtonClicked(11); });
    connect(ui -> btn_12, &QPushButton::clicked, [=](){ this-> pushButtonClicked(12); });
    connect(ui -> btn_13, &QPushButton::clicked, [=](){ this-> pushButtonClicked(13); });
    connect(ui -> btn_14, &QPushButton::clicked, [=](){ this-> pushButtonClicked(14); });
    connect(ui -> btn_15, &QPushButton::clicked, [=](){ this-> pushButtonClicked(15); });
    connect(ui -> btn_16, &QPushButton::clicked, [=](){ this-> pushButtonClicked(16); });
    connect(ui -> btn_17, &QPushButton::clicked, [=](){ this-> pushButtonClicked(17); });
    connect(ui -> btn_18, &QPushButton::clicked, [=](){ this-> pushButtonClicked(18); });
    connect(ui -> btn_19, &QPushButton::clicked, [=](){ this-> pushButtonClicked(19); });
    connect(ui -> btn_20, &QPushButton::clicked, [=](){ this-> pushButtonClicked(20); });
    connect(ui -> btn_21, &QPushButton::clicked, [=](){ this-> pushButtonClicked(21); });
    connect(ui -> btn_22, &QPushButton::clicked, [=](){ this-> pushButtonClicked(22); });
    connect(ui -> btn_23, &QPushButton::clicked, [=](){ this-> pushButtonClicked(23); });
    connect(ui -> btn_24, &QPushButton::clicked, [=](){ this-> pushButtonClicked(24); });
    connect(ui -> btn_25, &QPushButton::clicked, [=](){ this-> pushButtonClicked(25); });
    connect(ui -> btn_26, &QPushButton::clicked, [=](){ this-> pushButtonClicked(26); });
    connect(ui -> btn_27, &QPushButton::clicked, [=](){ this-> pushButtonClicked(27); });
    connect(ui -> btn_28, &QPushButton::clicked, [=](){ this-> pushButtonClicked(28); });
    connect(ui -> btn_29, &QPushButton::clicked, [=](){ this-> pushButtonClicked(29); });
    connect(ui -> btn_30, &QPushButton::clicked, [=](){ this-> pushButtonClicked(30); });
    connect(ui -> btn_31, &QPushButton::clicked, [=](){ this-> pushButtonClicked(31); });
    connect(ui -> btn_32, &QPushButton::clicked, [=](){ this-> pushButtonClicked(32); });
    connect(ui -> btn_33, &QPushButton::clicked, [=](){ this-> pushButtonClicked(33); });
    connect(ui -> btn_34, &QPushButton::clicked, [=](){ this-> pushButtonClicked(34); });
    connect(ui -> btn_35, &QPushButton::clicked, [=](){ this-> pushButtonClicked(35); });
    connect(ui -> btn_36, &QPushButton::clicked, [=](){ this-> pushButtonClicked(36); });
    connect(ui -> btn_37, &QPushButton::clicked, [=](){ this-> pushButtonClicked(37); });
    connect(ui -> btn_38, &QPushButton::clicked, [=](){ this-> pushButtonClicked(38); });
    connect(ui -> btn_39, &QPushButton::clicked, [=](){ this-> pushButtonClicked(39); });
    connect(ui -> btn_40, &QPushButton::clicked, [=](){ this-> pushButtonClicked(40); });
    connect(ui -> btn_41, &QPushButton::clicked, [=](){ this-> pushButtonClicked(41); });
    connect(ui -> btn_42, &QPushButton::clicked, [=](){ this-> pushButtonClicked(42); });
    connect(ui -> btn_43, &QPushButton::clicked, [=](){ this-> pushButtonClicked(43); });
    connect(ui -> btn_44, &QPushButton::clicked, [=](){ this-> pushButtonClicked(44); });
    connect(ui -> btn_45, &QPushButton::clicked, [=](){ this-> pushButtonClicked(45); });
    connect(ui -> btn_46, &QPushButton::clicked, [=](){ this-> pushButtonClicked(46); });
    connect(ui -> btn_47, &QPushButton::clicked, [=](){ this-> pushButtonClicked(47); });
    connect(ui -> btn_48, &QPushButton::clicked, [=](){ this-> pushButtonClicked(48); });
    connect(ui -> btn_49, &QPushButton::clicked, [=](){ this-> pushButtonClicked(49); });
    connect(ui -> btn_50, &QPushButton::clicked, [=](){ this-> pushButtonClicked(50); });
    connect(ui -> btn_51, &QPushButton::clicked, [=](){ this-> pushButtonClicked(51); });
    connect(ui -> btn_52, &QPushButton::clicked, [=](){ this-> pushButtonClicked(52); });
    connect(ui -> btn_53, &QPushButton::clicked, [=](){ this-> pushButtonClicked(53); });
    connect(ui -> btn_54, &QPushButton::clicked, [=](){ this-> pushButtonClicked(54); });
    connect(ui -> btn_55, &QPushButton::clicked, [=](){ this-> pushButtonClicked(55); });
    connect(ui -> btn_56, &QPushButton::clicked, [=](){ this-> pushButtonClicked(56); });
    connect(ui -> btn_57, &QPushButton::clicked, [=](){ this-> pushButtonClicked(57); });
    connect(ui -> btn_58, &QPushButton::clicked, [=](){ this-> pushButtonClicked(58); });
    connect(ui -> btn_59, &QPushButton::clicked, [=](){ this-> pushButtonClicked(59); });
    connect(ui -> btn_60, &QPushButton::clicked, [=](){ this-> pushButtonClicked(60); });
    connect(ui -> btn_61, &QPushButton::clicked, [=](){ this-> pushButtonClicked(61); });
    connect(ui -> btn_62, &QPushButton::clicked, [=](){ this-> pushButtonClicked(62); });
    connect(ui -> btn_63, &QPushButton::clicked, [=](){ this-> pushButtonClicked(63); });
    connect(ui -> btn_64, &QPushButton::clicked, [=](){ this-> pushButtonClicked(64); });

}

void scene::pushButtonClicked(int btn_no)
{

    if(btn_no == 1)
    {
        select_bttn(ui -> btn_1, 0 ,0);
    }
    else if (btn_no == 2)
    {
        select_bttn(ui -> btn_2, 0 ,1);
    }
    else if (btn_no == 3)
    {
        select_bttn(ui -> btn_3, 0 ,2);
    }
    else if (btn_no == 4)
    {
        select_bttn(ui -> btn_4, 0 ,3);
    }
    else if (btn_no == 5)
    {
        select_bttn(ui -> btn_5, 0 ,4);
    }
    else if (btn_no == 6)
    {
        select_bttn(ui -> btn_6, 0 ,5);
    }
    else if (btn_no == 7)
    {
        select_bttn(ui -> btn_7, 0 ,6);
    }
    else if (btn_no == 8)
    {
        select_bttn(ui -> btn_8, 0 ,7);
    }
    else if (btn_no == 9)
    {
        select_bttn(ui -> btn_9, 1, 0);
    }
    else if (btn_no == 10)
    {
        select_bttn(ui -> btn_10, 1, 1);
    }
    else if (btn_no == 11)
    {
        select_bttn(ui -> btn_11, 1, 2);
    }
    else if (btn_no == 12)
    {
        select_bttn(ui -> btn_12, 1, 3);
    }
    else if (btn_no == 13)
    {
        select_bttn(ui -> btn_13, 1, 4);
    }
    else if (btn_no == 14)
    {
        select_bttn(ui -> btn_14, 1, 5);
    }
    else if (btn_no == 15)
    {
        select_bttn(ui -> btn_15, 1, 6);
    }
    else if (btn_no == 16)
    {
        select_bttn(ui -> btn_16, 1 ,7);
    }
    else if (btn_no == 17)
    {
        select_bttn(ui -> btn_17, 2, 0);
    }
    else if (btn_no == 18)
    {
        select_bttn(ui -> btn_18, 2, 1);
    }
    else if (btn_no == 19)
    {
        select_bttn(ui -> btn_19, 2, 2);
    }
    else if (btn_no == 20)
    {
        select_bttn(ui -> btn_20, 2, 3);
    }
    else if (btn_no == 21)
    {
        select_bttn(ui -> btn_21, 2, 4);
    }
    else if (btn_no == 22)
    {
        select_bttn(ui -> btn_22, 2, 5);
    }
    else if (btn_no == 23)
    {
        select_bttn(ui -> btn_23, 2, 6);
    }
    else if (btn_no == 24)
    {
        select_bttn(ui -> btn_24, 2, 7);
    }
    else if (btn_no == 25)
    {
        select_bttn(ui -> btn_25, 3, 0);
    }
    else if (btn_no == 26)
    {
        select_bttn(ui -> btn_26, 3, 1);
    }
    else if (btn_no == 27)
    {
        select_bttn(ui -> btn_27, 3, 2);
    }
    else if (btn_no == 28)
    {
        select_bttn(ui -> btn_28, 3, 3);
    }
    else if (btn_no == 29)
    {
        select_bttn(ui -> btn_29, 3, 4);
    }
    else if (btn_no == 30)
    {
        select_bttn(ui -> btn_30, 3, 5);
    }
    else if (btn_no == 31)
    {
        select_bttn(ui -> btn_31, 3, 6);
    }
    else if (btn_no == 32)
    {
        select_bttn(ui -> btn_32, 3, 7);
    }
    else if (btn_no == 33)
    {
        select_bttn(ui -> btn_33, 4, 0);
    }
    else if (btn_no == 34)
    {
        select_bttn(ui -> btn_34, 4, 1);
    }
    else if (btn_no == 35)
    {
        select_bttn(ui -> btn_35, 4, 2);
    }
    else if (btn_no == 36)
    {
        select_bttn(ui -> btn_36, 4, 3);
    }
    else if (btn_no == 37)
    {
        select_bttn(ui -> btn_37, 4, 4);
    }
    else if (btn_no == 38)
    {
        select_bttn(ui -> btn_38, 4, 5);
    }
    else if (btn_no == 39)
    {
        select_bttn(ui -> btn_39, 4, 6);
    }
    else if (btn_no == 40)
    {
        select_bttn(ui -> btn_40, 4, 7);
    }
    else if (btn_no == 41)
    {
        select_bttn(ui -> btn_41, 5, 0);
    }
    else if (btn_no == 42)
    {
        select_bttn(ui -> btn_42, 5, 1);
    }
    else if (btn_no == 43)
    {
        select_bttn(ui -> btn_43, 5, 2);
    }
    else if (btn_no == 44)
    {
        select_bttn(ui -> btn_44, 5, 3);
    }
    else if (btn_no == 45)
    {
        select_bttn(ui -> btn_45, 5, 4);
    }
    else if (btn_no == 46)
    {
        select_bttn(ui -> btn_46, 5, 5);
    }
    else if (btn_no == 47)
    {
        select_bttn(ui -> btn_47, 5, 6);
    }
    else if (btn_no == 48)
    {
        select_bttn(ui -> btn_48, 5, 7);
    }
    else if (btn_no == 49)
    {
        select_bttn(ui -> btn_49, 6, 0);
    }
    else if (btn_no == 50)
    {
        select_bttn(ui -> btn_50, 6, 1);
    }
    else if (btn_no == 51)
    {
        select_bttn(ui -> btn_51, 6, 2);
    }
    else if (btn_no == 52)
    {
        select_bttn(ui -> btn_52, 6, 3);
    }
    else if (btn_no == 53)
    {
        select_bttn(ui -> btn_53, 6, 4);
    }
    else if (btn_no == 54)
    {
        select_bttn(ui -> btn_54, 6, 5);
    }
    else if (btn_no == 55)
    {
        select_bttn(ui -> btn_55, 6, 6);
    }
    else if (btn_no == 56)
    {
        select_bttn(ui -> btn_56, 6, 7);
    }
    else if (btn_no == 57)
    {
        select_bttn(ui -> btn_57, 7, 0);
    }
    else if (btn_no == 58)
    {
        select_bttn(ui -> btn_58, 7, 1);
    }
    else if (btn_no == 59)
    {
        select_bttn(ui -> btn_59, 7, 2);
    }
    else if (btn_no == 60)
    {
        select_bttn(ui -> btn_60, 7, 3);
    }
    else if (btn_no == 61)
    {
        select_bttn(ui -> btn_61, 7, 4);
    }
    else if (btn_no == 62)
    {
        select_bttn(ui -> btn_62, 7, 5);
    }
    else if (btn_no == 63)
    {
        select_bttn(ui -> btn_63, 7, 6);
    }
    else if (btn_no == 64)
    {
        select_bttn(ui -> btn_64, 7, 7);
    }
}

void scene::product_timer(QTimer *timer, QPushButton *button, QString product)
{
    int remainingTime = button->property("remainingTime").toInt();
    remainingTime -= 1;
    button->setProperty("remainingTime", remainingTime);
    if (button -> property("product") != " ")
    {
        button -> setText(QString::number(remainingTime));
    }
    else
    {
        timer -> deleteLater();
    }

    if (remainingTime == 0)
    {
        if (button->property("product") == "milk_cow")
        {
            button -> setStyleSheet(QString("border-image:url(icons/milk.png);"));
        }
        else if (button->property("product") == "milk_shep")
        {
            button -> setStyleSheet(QString("border-image:url(icons/milk.png);"));
        }
        else if(button->property("product") == "egg"){
            button -> setStyleSheet(QString("border-image:url(icons/egg.png);"));
        }
        else if(button->property("product") == "grain_flour"){
            button -> setStyleSheet(QString("border-image:url(icons/grain_flour.jpg);"));
        }
        else if(button->property("product") == "flour"){
            button -> setStyleSheet(QString("border-image:url(icons/flour.png);"));
        }
    }
    else if (remainingTime < 0)
    {
        if (button->property("product") == "milk_cow")
        {
            if(remainingTime <= -15)
            {
                timer->stop();
                timer -> deleteLater();
                button -> setText(" ");
            }
        }
        else if (button->property("product") == "milk_shep")
        {
            if(remainingTime <= -12)
            {
                timer->stop();
                timer -> deleteLater();
                button -> setText(" ");
            }
        }
        else if(button->property("product") == "egg")
        {
            if(remainingTime <= -15)
            {
                timer->stop();
                timer -> deleteLater();
                button -> setText(" ");
            }
        }
        else if(button->property("product") == "grain_flour")
        {
            if(remainingTime <= -20)
            {
                timer->stop();
                timer -> deleteLater();
                button -> setText(" ");
            }
        }
        else if(button->property("product") == "flour")
        {
            if(remainingTime <= -36)
            {
                timer->stop();
                timer -> deleteLater();
                button -> setText(" ");
            }
        }
    }
}

void scene::timerTick1()
{
    remanningTime--;

    ui -> lbl_timer -> setText("Time: ( " +QString::number(remanningTime) + " s )");

    if(remanningTime == 0)
    {
        QMessageBox::information(0, "Time Over", "Time Over");
        this -> setDisabled(true);

        QSqlQuery query;
        query.prepare("UPDATE game_users SET user_farmId=:coins WHERE user_name=:name");
        query.bindValue(":coins", coins);
        query.bindValue(":name", user_name);

        query.exec();

        if(remaining_players == 1 || remaining_players == 0)
        {
            this -> hide();
            result *show_winner = new result();
            show_winner->show();
        }
        else
        {
            this -> hide();
            scene *new_scene = new scene(remaining_players - 1, user_names_lst);
            new_scene->show();
        }
    }
}

void scene::buy_wrkr()
{
    coins = coins - 5;
    ui -> lbl_coins -> setText("Coins: " + QString::number(coins));

    workers = workers + 1;
    ui -> lbl_no_wrkrs->setText("No. of Workers: " + QString::number(workers));
}

void scene::initDB()
{
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../uni_game.db");
    if(!db.open())
        QMessageBox::warning(nullptr,"Database","Could not connect to database");
}
