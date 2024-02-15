#include "login.h"
#include "ui_login.h"
#include "scene.h"

#include <QMessageBox>
#include <qdebug.h>
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

using namespace std;


string cpt;
int number_of_players;
int i=1;
bool show_pass = 0;
//################################################ captcha
bool checkCaptcha(string captcha, string user_captcha)
{
    return captcha.compare(user_captcha) == 0;
}

string generateCaptcha(int n)
{
    time_t t;
    srand((unsigned)time(&t));

    char* chrs = "abcdefghijklmnopqrstuvwxyzABCDEFGHI"
                 "JKLMNOPQRSTUVWXYZ0123456789";

    string captcha = "";
    while (n--)
        captcha.push_back(chrs[rand() % 62]);

    return captcha;
}

//################################################ Read Json
void Login::printJsonData()
{

    QFile file("C:/Users/Seyyed Javad Razavi/Desktop/game/transformed_path_to_input_file.json");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    QStringList name_lst;
    QString name;
    QStringList code_lst;
    QString code;
    QStringList img_path_lst;
    QString img_path;

    int st = 0;
    while(!in.atEnd()) {
        QString line = in.readLine();
//        qDebug() << line;
        if(line.contains("name"))
        {
            name_lst = line.split('"');
            name = name_lst[3];
        }
        else if(line.contains("code"))
        {
            code_lst = line.split('"');
            code = code_lst[3];
        }
        else if(line.contains("flag"))
        {
            img_path_lst= line.split("/");
            img_path = img_path_lst[img_path_lst.length()-1];

            st = 1;
        }

        if(st == 1)
        {
            QStringList path = img_path.split('"');
            QString url = "C:/Users/Seyyed Javad Razavi/Desktop/game/flags/" + path[0];
            QPixmap img(url);

            name = name + ", +" + code;
             ui->cb_country_code->addItem(img, name);

            st = 0;
        }

    }
    file.close();
}


//#################################################  Main
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->pass->setEchoMode(QLineEdit::Password);
}

Login::Login(int num) :
    QDialog(nullptr),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this -> setStyleSheet("background-color: rgb(57, 183, 208);");
    ui->pass->setEchoMode(QLineEdit::Password);
    number_of_players = num;
    qDebug() << num;

    ui -> lbl_number -> setText(ui -> lbl_number -> text() + " 1");

    cpt = generateCaptcha(3);
    ui -> lbl_captcha -> setText(QString::fromStdString(cpt));
    ui -> phone -> setValidator(new QIntValidator(0, 99999999999, this));

    initDB();

    printJsonData();

    ui -> btn_show_hide_pass ->setStyleSheet("border-image:url(C:/Users/Seyyed Javad Razavi/Desktop/game/Source/icons/show.jpg);");
}

Login::~Login()
{
    delete ui;
}

QString Login::getPlayerUserName()
{
    return ui->user_name->text();
}

QString Login::getPlayerEmail()
{
    return ui->email->text();
}

QString Login::getPlayerPass()
{
    return ui->pass->text();
}

float Login::getPlayerBalace()
{
    return ui->balance->value();
}

QString Login::getPhoneNumber()
{
    return ui->phone->text();
}

QString Login::getCountryCode()
{
    return ui->cb_country_code->currentText();

}

QString Login::getCaptcha()
{
    return ui->captcha->text();
}

void Login::userRegister()
{
    QStringList email = getPlayerEmail().split('@');
    bool status = 1;
    QMessageBox ms;

    if(getPlayerEmail() == "")
    {
        QMessageBox::warning(this,"خطا","وارد کردن ایمیل ضروری است !");
        status = 0;
    }
    else if(getPlayerEmail().contains("*") || getPlayerEmail().contains("+") ||
            getPlayerEmail().contains("-") || getPlayerEmail().contains("/") ||
            getPlayerEmail().contains("$") || getPlayerEmail().contains("(") ||
            getPlayerEmail().contains(")") || getPlayerEmail().contains("#") ||
            getPlayerEmail().contains("^") || getPlayerEmail().contains("%"))
    {
        QMessageBox::warning(this,"خطا"," ایمیل شما باید فاقد کاراکترهای * + - / $ ( ) # ^ % باشد");
        status = 0;
    }
    else if(email[1]!="gmail.com" && email[1]!="email.com" && email[1]!="mail.um.ac")
    {
        QMessageBox::warning(this,"خطا","ایمیل شما باید به یکی از 3 فرمت gmail.com و یا email.com و mail.um.ac ختم شود.");
        status = 0;
    }
    else if(getPlayerPass() == "")
    {
        QMessageBox::warning(this,"خطا","وارد کردن پسورد ضروری است!");
        status = 0;
    }
    else if(getPlayerPass().contains("*") || getPlayerPass().contains("+") ||
            getPlayerPass().contains("-") || getPlayerPass().contains("/") ||
            getPlayerPass().contains("$") || getPlayerPass().contains("(") ||
            getPlayerPass().contains(")") || getPlayerPass().contains("#") ||
            getPlayerPass().contains("^") || getPlayerPass().contains("%"))
    {
        QMessageBox::warning(this,"خطا","پسورد شما نباید شامل کاراکترهای خاص باشد!");
        status = 0;

    }
    else if(getPlayerUserName() == "")
    {
        QMessageBox::warning(this,"خطا","وارد کردن نام کاربری ضروری است!");
        status = 0;
    }
    else if(getPlayerBalace() <= 0.00)
    {
        QMessageBox::warning(this,"خطا","مقدار موجودی نمتواند خالی و یا صفر باشد!");
        status = 0;
    }
    else if(getCountryCode() == "")
    {
        QMessageBox::warning(this,"خطا","وارد کردن کد کشور ضروری است !");
        status = 0;
    }
    else if(getPhoneNumber() == "")
    {
        QMessageBox::warning(this,"خطا","وارد کردن شماره تماس ضروری است !");
        status = 0;
    }
    else if (!checkCaptcha(cpt, ui -> captcha -> text().toStdString()))
    {
        QMessageBox::warning(this,"خطا","مقدار کد کپچا را درست وارد کنید!");
        status = 0;
    }

    if (status == 1)
    {
        QString slcted_cntry = getCountryCode();
        slcted_cntry = slcted_cntry.split("+")[1];

        QSqlQuery query;
        QString insrt_qry = "INSERT INTO game_users (user_Name, user_email, user_password, user_balance, user_phoneNumber, user_countryCode, user_farmId)   values('"
                + getPlayerUserName() + "' , '" + getPlayerEmail() + "' , '" + getPlayerPass() + "' , '"
                + QString::number(getPlayerBalace()) + "' , '" + getPhoneNumber() + "' , '" +  slcted_cntry + "' , '" + QString::number(1) +"');";
//        qDebug() << insrt_qry;
        query.exec(insrt_qry);

        ui -> lbl_number -> setText("Player Number " + QString::number(i+1));
        i+= 1;
        captcha_regen();
    }


    if (i == (number_of_players+1))
    {
        QMessageBox::warning(this, "", "اطلاعات برای شروع بازی کامل شده است");

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
        scenes -> show();
        this -> hide();
    }
}

void Login::show_hide_password()
{
    if(show_pass)
    {
        ui -> btn_show_hide_pass -> setStyleSheet("border-image:url(C:/Users/Seyyed Javad Razavi/Desktop/game/Source/icons/show.jpg);");
        ui->pass->setEchoMode(QLineEdit::Password);
        show_pass = 0;
    }
    else
    {
        ui -> btn_show_hide_pass -> setStyleSheet("border-image:url(C:/Users/Seyyed Javad Razavi/Desktop/game/Source/icons/hide.jpg);");
        ui->pass->setEchoMode(QLineEdit::Normal);
        show_pass = 1;
    }
}

void Login::captcha_regen()
{
    cpt = generateCaptcha(3);
    ui -> lbl_captcha -> setText(QString::fromStdString(cpt));
}

void Login::initDB()
{
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Seyyed Javad Razavi/Desktop/game/uni_game.db");
    if(!db.open())
        QMessageBox::warning(nullptr,"Database","Could not connect to database");
}

void Login::on_spinBox_valueChanged()
{
    float money = ui->balance->value();
    money = floor(money);
    ui -> balance -> setValue(money);
}

void Login::pass_check()
{
    QString pp = ui -> pass -> text();
//    if (pp[pp.length() - 1s] == )

    if(getPlayerPass().endsWith("*") || getPlayerPass().endsWith("+") ||
                getPlayerPass().endsWith("-") || getPlayerPass().endsWith("/") ||
                getPlayerPass().endsWith("$") || getPlayerPass().endsWith("(") ||
                getPlayerPass().endsWith(")") || getPlayerPass().endsWith("#") ||
                getPlayerPass().endsWith("^") || getPlayerPass().endsWith("%") ||
            getPlayerPass().endsWith("!") || getPlayerPass().endsWith("@") ||
            getPlayerPass().endsWith("&") || getPlayerPass().endsWith("_"))
    {
        ui -> pass -> setText(pp.mid(0, (pp.length()-1)));
    }

}



