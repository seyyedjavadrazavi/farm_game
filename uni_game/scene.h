#ifndef SCENE_H
#define SCENE_H

#include <QMainWindow>
#include <QPushButton>
#include <QtMultimedia>

namespace Ui {
class scene;
}

class scene : public QMainWindow
{
    Q_OBJECT

public:
    explicit scene(QWidget *parent = nullptr);
    ~scene();
    scene(int number_of_players, QList<QString> user_name);

private:
    Ui::scene *ui;

    int remanningTime = 90;
    int remaining_players = 0;
    int boarder[8][8] = {{0}};
    int coins = 10;
    int workers = 1;
    int rd_btn_slction();
    void select_bttn(QPushButton *button, int i, int j);
    QList<QTimer> *timers;
    QString user_name;
    QList<QString> user_names_lst;
    void initDB();
    QMediaPlayer *m_player;

private slots:
    void buttons_stup();
    void pushButtonClicked(int bottun_name);
    void timerTick1();
    void buy_wrkr();
    void product_timer(QTimer *timer, QPushButton *button, QString product);
};

#endif // SCENE_H
