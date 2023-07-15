#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "workingwithtable.h"

#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
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
        data.push_back(QVector<QString> {numberOfFlight, nameOfAirline, onBoardNumber, departureAirport, arrivialAirport});
        addNode(ui->flights, numberOfFlight, nameOfAirline, onBoardNumber, departureAirport, arrivialAirport);
    }
    else {
        QMessageBox::warning(this, "Ошибка", "Нельзя добавить один и тот же рейс");
    }
}

void MainWindow::recieveSearchResoults(int steps, QVector<QString> resoult)
{

}

void MainWindow::on_removeFlight_clicked()
{
    auto select = ui->flights->selectionModel()->selectedRows();
    if(select.count() > 0) {
        int rowNumber = select.constFirst().row();
        ui->flights->removeRow(rowNumber);
        //qDebug() << data[rowNumber][0];
        data.remove(rowNumber);
    }
}


void MainWindow::on_search_clicked()
{
    srch = new searchModal(this);
    connect(srch, &searchModal::sentSearchedData, this, &MainWindow::recieveSearchResoults);
    connect(this, &MainWindow::sentDataToSearch, srch, &searchModal::recieveDataToSeacrh);
    emit sentDataToSearch(data);
    srch->setModal(true);
    srch->exec();

}


void MainWindow::on_open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть"), "./", tr("Text Files (*.txt)"));
    //auto file = QFileDialog::getOpenFileUrl(this, tr("Открыть"), "./", tr("Text Files (*.txt)"));
    qDebug() << fileName << "\n";
}

