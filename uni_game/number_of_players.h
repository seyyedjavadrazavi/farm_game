#ifndef NUMBER_OF_PLAYERS_H
#define NUMBER_OF_PLAYERS_H

#include <QDialog>

namespace Ui {
class number_of_players;
}

class number_of_players : public QDialog
{
    Q_OBJECT

public:
    explicit number_of_players(QWidget *parent = nullptr);

    number_of_players(QString);

    ~number_of_players();

private:
    Ui::number_of_players *ui;

private slots:
    int numberOfUsers();
};

#endif // NUMBER_OF_PLAYERS_H
