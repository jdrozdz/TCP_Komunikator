#include "logowanie.h"
#include "ui_logowanie.h"

Logowanie::Logowanie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Logowanie)
{
    ui->setupUi(this);

    ui->label_2->setVisible(false);
    ui->label_2->setStyleSheet("color: red; font-weight: bold; font-size: 10px;");

}

Logowanie::~Logowanie()
{
    delete ui;
}

void Logowanie::on_pushButton_released() {

    QString username = ui->lineEdit->text();

    if(username.length() > 0){

        MainWindow *w = new MainWindow();
        w->setUsername(username);
        w->show();
        this->hide();

    }else{
        ui->label_2->setVisible(true);
    }
}
