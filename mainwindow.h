#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHeaderView>
#include "addflightmodal.h"
#include "searchmodal.h"
#include "showhashfunction.h"
#include "showtrees.h"
#include "avltree.h"
#include "hashtable.h"
#include <QTableWidget>
#include <QVector>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QStringList>
#include <QTextStream>
#include "validation.h"


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

    void on_showHashFunction_triggered();

    void on_showTree_triggered();

    void on_save_triggered();


    void on_cleanSearch_clicked();

private:
    QVector<QVector<QString>> data; // массив сходных данных
    void refillTable();
    Ui::MainWindow *ui;
    addFlightModal *afm; // модальное окно добавления записи
    AVLTree a0 = AVLTree(0);
    AVLTree a1 = AVLTree(1);
    AVLTree a2 = AVLTree(2);
    AVLTree a3 = AVLTree(3);
    AVLTree a4 = AVLTree(4);
    HashTable ht = HashTable(20);
    searchModal *srch;
    ShowHashFunction *shf;
    ShowTrees *st;
    QTableWidget* resoults;
public slots:
    void recieveNode(QString numberOfFlight, QString nameOfAirline, QString onBoardNumber,QString departureAirport ,QString arrivialAirport);
    void recieveSearchResoults(int searchCase, QString toSearch);
};
#endif // MAINWINDOW_H
