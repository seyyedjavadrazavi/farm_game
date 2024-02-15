#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

    Login(int);

    ~Login();

    QString getPlayerUserName();
    QString getPlayerEmail();
    QString getPlayerPass();
    float getPlayerBalace();
    QString getPhoneNumber();
    QString getCountryCode();
    QString getCaptcha();
    void initDB();
    void printJsonData();

private:
    Ui::Login *ui;

private slots:
    void userRegister();
    void captcha_regen();
    void show_hide_password();
    void on_spinBox_valueChanged();
    void pass_check();
};

#endif // LOGIN_H
