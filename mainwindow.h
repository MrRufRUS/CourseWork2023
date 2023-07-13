#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addflightmodal.h"
#include "searchmodal.h"
#include <QTableView>
#include <QVector>

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

    void on_removeFlight_clicked();

    void on_search_clicked();

    void on_open_triggered();

private:
    QVector<QVector<QString>> data; // массив сходных данных

    Ui::MainWindow *ui;
    addFlightModal *afm; // модальное окно добавления записи
    searchModal *srch;
public slots:
    void recieveNode(QString numberOfFlight, QString nameOfAirline, QString onBoardNumber,QString departureAirport ,QString arrivialAirport);
    void recieveSearchResoults(int steps, QVector<QString> resoult);
signals:
    void sentDataToSearch(QVector<QVector<QString>>&);
};
#endif // MAINWINDOW_H
