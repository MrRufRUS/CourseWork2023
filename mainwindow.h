#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addflightmodal.h"
#include <QTableView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addFlight_clicked();

private:
    Ui::MainWindow *ui;
    addFlightModal *afm;
public slots:
    void recieveNode(QString numberOfFlight, QString nameOfAirline, QString onBoardNumber,QString departureAirport ,QString arrivialAirport);
};
#endif // MAINWINDOW_H
