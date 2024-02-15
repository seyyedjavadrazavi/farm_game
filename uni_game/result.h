#ifndef RESULT_H
#define RESULT_H

#include <QDialog>

namespace Ui {
class result;
}

class result : public QDialog
{
    Q_OBJECT

public:
    explicit result(QWidget *parent = nullptr);
    ~result();

private:
    Ui::result *ui;

    void initDB();
};

#endif // RESULT_H
