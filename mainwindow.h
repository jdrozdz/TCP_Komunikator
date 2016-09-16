#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtNetwork>
#include <QTcpSocket>
#include <QTcpServer>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setUsername(QString);

private slots:
    void on_sendButton_released();

    void on_clearButton_released();

    void newConnection();

    void on_serverStartButton_released();
    void readyRead();

signals:

private:
    Ui::MainWindow *ui;
    QString username;
    QTcpServer *server;
    QTcpSocket *socket;
    QString log;
    int ClientID;
    bool serverStarted;
};

#endif // MAINWINDOW_H
