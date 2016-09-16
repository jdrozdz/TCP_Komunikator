#ifndef LOGOWANIE_H
#define LOGOWANIE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Logowanie;
}

class Logowanie : public QDialog
{
    Q_OBJECT

public:
    explicit Logowanie(QWidget *parent = 0);
    ~Logowanie();

private slots:
    void on_pushButton_released();

private:
    Ui::Logowanie *ui;
};

#endif // LOGOWANIE_H
