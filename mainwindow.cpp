#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "workingwithtable.h"


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
        a0.deleteElem(data[rowNumber]);
        a1.deleteElem(data[rowNumber]);
        a2.deleteElem(data[rowNumber]);
        a3.deleteElem(data[rowNumber]);
        a4.deleteElem(data[rowNumber]);
        ht.remove(data[rowNumber][0]);
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
    data.clear();
    a0 = AVLTree(0);
    a0 = AVLTree(1);
    a0 = AVLTree(2);
    a0 = AVLTree(3);
    a0 = AVLTree(4);
    ht = HashTable(20);
    ui->flights->setRowCount(0);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть"), "./", tr("Text Files (*.txt)"));
    //auto file = QFileDialog::getOpenFileUrl(this, tr("Открыть"), "./", tr("Text Files (*.txt)"));
    qDebug() << fileName << "\n";
    QFile fin(fileName);
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&fin);
    QString buffer;
    if(fin.isOpen()) {
        while (!fin.atEnd()) {
            buffer = fin.readLine().trimmed();
            QVector<QString> listBuffer = buffer.split(";").toVector();
            if (listBuffer.at(0).size() < 5) {
                QMessageBox::warning(this, "Ошибка", "Номер рейса должен содержать минимум 5 символов");
                return;
            }
            if(!validateData(listBuffer.at(0))) {
                QMessageBox::warning(this, "Ошибка", "Номер рейса должен содержать только заглавные латинские литеры, цифры и \"-\"");
                return;
            }
            if (listBuffer.at(1).size() == 0) {
                QMessageBox::warning(this, "Ошибка", "Название авиакомпании не может быть пустым");
                return;
            }
            if(!validateASCII(listBuffer.at(1)))
            {
                QMessageBox::warning(this, "Ошибка", "Введено неверное название авиакомпанни");
                return;
            }
            if (listBuffer.at(2).size() == 0) {
                QMessageBox::warning(this, "Ошибка", "Бортовой номер не может быть пустым");
                return;
            }
            if(!validateData(listBuffer.at(2))) {
                QMessageBox::warning(this, "Ошибка", "Бортовой номер должен содержать только заглавные латинские литеры, цифры и \"-\"");
                return;
            }
            if (listBuffer.at(3).size() != 4) {
                QMessageBox::warning(this, "Ошибка", "Код ИКАО аэропорта вылета должен содержать 4 символа");
                return;
            }
            for (auto ch : listBuffer.at(3)) {
                if(!((ch.unicode() <= 90 && ch.unicode() >= 65) || (ch.unicode() <= 57 && ch.unicode() >= 48))) {
                    QMessageBox::warning(this, "Ошибка", "ИКАО аэропорта отлёта должен содержать только заглавные латинские литеры и цифры");
                    return;
                }
            }
            if (listBuffer.at(4).size() != 4) {
                QMessageBox::warning(this, "Ошибка", "Код ИКАО аэропорта прилета должен содержать 4 символа");
                return;
            }
            for (auto ch : listBuffer.at(4)) {
                if(!((ch.unicode() <= 90 && ch.unicode() >= 65) || (ch.unicode() <= 57 && ch.unicode() >= 48))) {
                    QMessageBox::warning(this, "Ошибка", "ИКАО аэропорта прилёта должен содержать только заглавные латинские литеры и цифры");
                    return;
                }
            }
            if(listBuffer.size() == 5) {
                a0.insert(listBuffer);
                a1.insert(listBuffer);
                a2.insert(listBuffer);
                a3.insert(listBuffer);
                a4.insert(listBuffer);
                ht.add(listBuffer);
                data.push_back(listBuffer);
                addNode(ui->flights, listBuffer);
            }
        }

    }
    fin.close();
}


void MainWindow::on_showHashFunction_triggered()
{
    ht.print();
    shf = new ShowHashFunction(this);
    shf->setModal(true);
    shf->exec();
}


void MainWindow::on_showTree_triggered()
{
    a0.print();
    a1.print();
    a2.print();
    a3.print();
    a4.print();

    st = new ShowTrees(this);
    st->setModal(true);
    st->exec();
}


void MainWindow::on_save_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Сохранить"), "./", tr("Text Files (*.txt)"));
    //auto file = QFileDialog::getOpenFileUrl(this, tr("Открыть"), "./", tr("Text Files (*.txt)"));
    qDebug() << fileName << "\n";
    QFile fout(fileName);
    fout.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&fout);
    if(fout.isOpen()) {
        for (int i = 0; i < data.size(); i++) {
            out << (data[i][0] + ";" + data[i][1] + ";" + data[i][2] + ";" + data[i][3] + ";" + data[i][4] + "\n");
        }
    }
    fout.close();
}

