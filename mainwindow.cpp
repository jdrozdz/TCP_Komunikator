#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    username = "anonymous";

    ui->chatContent->setEnabled(false);
    ui->chatContent->setStyleSheet("background: #fff;");
    ui->serverLog->setStyleSheet("background: #fff");


    QList<QHostAddress> ipList = QNetworkInterface::allAddresses();

    QRegExp ipPatern("[1:9]{1,3}\\.[0:9]{1,3}\\.[0:9]{1,3}\\.[1:9]{1,3}");
    QRegExpValidator validator(ipPatern,0);

    int pos = 0;

    for(int i=0;i<ipList.length();i++){
        QString ip = ipList[i].toString();
        qDebug() << ip << validator.validate(ip,pos);
        ui->ipLists->addItem(ip);
    }

    server = new QTcpServer(this);
    server->setProxy(QNetworkProxy::NoProxy);
    serverStarted = false;

    ClientID = 100;

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_released()
{
    if(ui->_userText->text().length() > 0){
        QString message = QString("<p style='background: #ccc; color: red;'><b>Ja:</b> <span style='color: #fff'>%1</span></p>").arg(ui->_userText->text());
        ui->chatContent->appendHtml(message);
        ui->_userText->clear();
    }
}

void MainWindow::on_clearButton_released()
{
    int a = QMessageBox::question(this, "Kasowowanie zawartości", "Czy napewno chcesz usunąć wprowadzony tekst?");

    if(a == QMessageBox::Yes){
        ui->_userText->clear();
    }
}

void MainWindow::setUsername(QString _user){
    this->username = _user;

    QListWidgetItem *newUser = new QListWidgetItem(_user);
    newUser->setIcon(QIcon(":/images/status_online"));
    newUser->setTextColor(QColor(0,0,250));

    ui->usersList->addItem(newUser);
}


void MainWindow::newConnection(){
    QString client_id = QString("ID:%1\r\n").arg(ClientID);
    ClientID++;
    socket = server->nextPendingConnection();

    socket->write("Connected\r\n");
    socket->write(client_id.toStdString().c_str());

    socket->flush();
    socket->waitForBytesWritten(3900);
    log = QString("<div style='color: #000066'>Nowy klient: %1</div>").arg(socket->peerAddress().toString());

    if(socket->bytesAvailable()){
        qDebug() << socket->readAll();
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    // socket->close();


    ui->serverLog->appendHtml(log);
}

void MainWindow::on_serverStartButton_released() {
    if(serverStarted == false){
        if(!server->listen((QHostAddress)ui->ipLists->currentText(), ui->serverPort->text().toInt())){
            log = QString("<div style='color: %2; font-weight: bold; padding: 3px;'>%1</div>").arg("Nie można utworzyć połączenia. Serwer nie wystartował! <br />[Error] "+server->errorString()).arg("red");
            qDebug() << "Server still stoped!" << server->errorString();
        }else{
            log = QString("<div style='color: %2; font-weight: bold; padding: 3px;'>%1</div>").arg("Serwer uruchomiony!").arg("blue");
            serverStarted = true;
            ui->serverPort->setEnabled(false);
            ui->ipLists->setEnabled(false);
            ui->serverStartButton->setText("Server Stop");
            ui->serverStartButton->setIcon(QIcon(":/images/computer_stop"));
            ui->serverStartButton->setIconSize(QSize(16,16));
            qDebug() << "Server started";

            connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
        }
    }else{
        qDebug() << "Server stoped";
        serverStarted = false;
        ui->serverPort->setEnabled(true);
        ui->ipLists->setEnabled(true);
        ui->serverStartButton->setText("Server Start");
        ui->serverStartButton->setIcon(QIcon(":/images/server_start"));
        ui->serverStartButton->setIconSize(QSize(16,16));
        log = QString("<div style='color: %2; font-weight: bold; padding: 3px;'>%1</div>").arg("Serwer zatrzymany").arg("green");
        server->close();
    }

    ui->serverLog->appendHtml(log);
}

void MainWindow::readyRead(){
    QString message = QString("<div style='color: #7093DB; font-weight: bold;'>Client send data: %1</div>").arg(socket->readAll().toStdString().c_str());
    ui->serverLog->appendHtml(message);
}
