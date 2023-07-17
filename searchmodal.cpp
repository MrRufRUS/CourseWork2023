#include "searchmodal.h"
#include "ui_searchmodal.h"
#include "validation.h"

searchModal::searchModal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchModal)
{
    ui->setupUi(this);
}

searchModal::~searchModal()
{
    delete ui;
}
template<typename T>
QVector<QVector<T>> naturalMergeSort(QVector<QVector<T>>& a, int size, int& col);
template<typename T>
void merge(QVector<QVector<T>>& A, int const startPos, int const nA, int const nB,
           QVector<QVector<T>>& C, int& col);
int binarySearch(QVector<QVector<QString>>& nums,int low, int high, QString& target, int& steps, int& col);
void searchModal::on_find_clicked()
{
    switch (col) {
    case 0:
        {
            if (ui->lineEdit->text().size() < 5) {
                QMessageBox::warning(this, "Ошибка", "Номер рейса должен содержать минимум 5 символов");
                return;
            }
            if(!validateData(ui->lineEdit->text())) {
                QMessageBox::warning(this, "Ошибка", "Номер рейса должен содержать только заглавные латинские литеры, цифры и \"-\"");
                return;
            }
            stringToSearch = ui->lineEdit->text();
            break;
        }
    case 1:
        {
            if (ui->lineEdit_2->text().size() == 0) {
                QMessageBox::warning(this, "Ошибка", "Название авиакомпании не может быть пустым");
                return;
            }
            if(!validateASCII(ui->lineEdit_2->text()))
            {
                QMessageBox::warning(this, "Ошибка", "Введено неверное название авиакомпанни");
                return;
            }
            stringToSearch = ui->lineEdit_2->text();
            break;
        }
    case 2:
        {
            if (ui->lineEdit_3->text().size() == 0) {
                QMessageBox::warning(this, "Ошибка", "Бортовой номер не может быть пустым");
                return;
            }
            if(!validateData(ui->lineEdit_3->text())) {
                QMessageBox::warning(this, "Ошибка", "Бортовой номер должен содержать только заглавные латинские литеры, цифры и \"-\"");
                return;
            }
            stringToSearch = ui->lineEdit_3->text();
            break;
        }
    case 3:
        {
            if (ui->lineEdit_4->text().size() != 4) {
                QMessageBox::warning(this, "Ошибка", "Код ИКАО аэропорта вылета должен содержать 4 символа");
                return;
            }
            for (QChar& ch : ui->lineEdit_4->text()) {
                if(!((ch.unicode() <= 90 && ch.unicode() >= 65) || (ch.unicode() <= 57 && ch.unicode() >= 48))) {
                    QMessageBox::warning(this, "Ошибка", "ИКАО аэропорта отлёта должен содержать только заглавные латинские литеры и цифры");
                    return;
                }
            }
            stringToSearch = ui->lineEdit_4->text();
            break;
        }
    case 4:
        {
            if (ui->lineEdit_5->text().size() != 4) {
                QMessageBox::warning(this, "Ошибка", "Код ИКАО аэропорта прилета должен содержать 4 символа");
                return;
            }
            for (QChar& ch : ui->lineEdit_5->text()) {
                if(!((ch.unicode() <= 90 && ch.unicode() >= 65) || (ch.unicode() <= 57 && ch.unicode() >= 48))) {
                    QMessageBox::warning(this, "Ошибка", "ИКАО аэропорта прилёта должен содержать только заглавные латинские литеры и цифры");
                    return;
                }
            }
            stringToSearch = ui->lineEdit_5->text();
            break;
        }
    default:
        break;
    }

    int steps = 0;

}

void searchModal::on_cancel_clicked()
{
    this->close();
}

void searchModal::recieveDataToSeacrh(QVector<QVector<QString>>& dataToSearch)
{
    dts = dataToSearch;
}


void searchModal::on_radioButton_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit->setDisabled(false);
    ui->lineEdit_2->setDisabled(true);
    ui->lineEdit_3->setDisabled(true);
    ui->lineEdit_4->setDisabled(true);
    ui->lineEdit_5->setDisabled(true);
    col = 0;
    ui->find->setDisabled(false);
}


void searchModal::on_radioButton_2_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit->setDisabled(true);
    ui->lineEdit_2->setDisabled(false);
    ui->lineEdit_3->setDisabled(true);
    ui->lineEdit_4->setDisabled(true);
    ui->lineEdit_5->setDisabled(true);
    col = 1;
    ui->find->setDisabled(false);
}


void searchModal::on_radioButton_3_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit->setDisabled(true);
    ui->lineEdit_2->setDisabled(true);
    ui->lineEdit_3->setDisabled(false);
    ui->lineEdit_4->setDisabled(true);
    ui->lineEdit_5->setDisabled(true);
    col = 2;
    ui->find->setDisabled(false);
}


void searchModal::on_radioButton_4_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit->setDisabled(true);
    ui->lineEdit_2->setDisabled(true);
    ui->lineEdit_3->setDisabled(true);
    ui->lineEdit_4->setDisabled(false);
    ui->lineEdit_5->setDisabled(true);
    col = 3;
    ui->find->setDisabled(false);
}

void searchModal::on_radioButton_5_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit->setDisabled(true);
    ui->lineEdit_2->setDisabled(true);
    ui->lineEdit_3->setDisabled(true);
    ui->lineEdit_4->setDisabled(true);
    ui->lineEdit_5->setDisabled(false);
    col = 4;
    ui->find->setDisabled(false);
}
