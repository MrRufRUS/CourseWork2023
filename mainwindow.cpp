#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "workingwithtable.h"

#include <QMessageBox>
//#include "addflightmodal.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addFlight_clicked()
{
    afm = new addFlightModal(this);
    connect(afm, &addFlightModal::sentForm, this, &MainWindow::recieveNode);
    afm->setModal(true);
    afm->exec();
}

void MainWindow::recieveNode(QString numberOfFlight, QString nameOfAirline, QString onBoardNumber, QString departureAirport, QString arrivialAirport)
{
    if(checkRepeat(ui->flights, numberOfFlight, 0)) {
        addNode(ui->flights, numberOfFlight, nameOfAirline, onBoardNumber, departureAirport, arrivialAirport);
    }
    else {
        QMessageBox::warning(this, "Ошибка", "Нельзя добавить один и тот же рейс");
    }
}

