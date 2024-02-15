#ifndef SENCE_H
#define SENCE_H

#include <QDialog>

namespace Ui {
class sence;
}

class sence : public QDialog
{
    Q_OBJECT

public:
    explicit sence(QWidget *parent = nullptr);
    ~sence();

private:
    Ui::sence *ui;
};

#endif // SENCE_H
