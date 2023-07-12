#include "addflightmodal.h"
#include "ui_addflightmodal.h"
#include "validation.h"
#include <QMessageBox>

addFlightModal::addFlightModal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addFlightModal)
{
    ui->setupUi(this);
}

addFlightModal::~addFlightModal()
{
    delete ui;
}

void addFlightModal::on_cancelButton_clicked()
{
    this->close();
}

void addFlightModal::on_addButton_clicked()
{
    if (ui->numberOfFlight->text().size() < 5) {
        QMessageBox::warning(this, "Ошибка", "Номер рейса должен содержать минимум 5 символов");
        return;
    }
    if(!validateData(ui->numberOfFlight->text())) {
        QMessageBox::warning(this, "Ошибка", "Номер рейса должен содержать только заглавные латинские литеры, цифры и \"-\"");
        return;
    }
    if (ui->nameOfAirline->text().size() == 0) {
        QMessageBox::warning(this, "Ошибка", "Название авиакомпании не может быть пустым");
        return;
    }
    if(!validateASCII(ui->nameOfAirline->text()))
    {
        QMessageBox::warning(this, "Ошибка", "Введено неверное название авиакомпанни");
        return;
    }
    if (ui->onBoardNumber->text().size() == 0) {
        QMessageBox::warning(this, "Ошибка", "Бортовой номер не может быть пустым");
        return;
    }
    if(!validateData(ui->onBoardNumber->text())) {
        QMessageBox::warning(this, "Ошибка", "Бортовой номер должен содержать только заглавные латинские литеры, цифры и \"-\"");
        return;
    }
    if (ui->departureAirport->text().size() != 4) {
        QMessageBox::warning(this, "Ошибка", "Код ИКАО аэропорта вылета должен содержать 4 символа");
        return;
    }
    for (QChar& ch : ui->departureAirport->text()) {
        if(!((ch.unicode() <= 90 && ch.unicode() >= 65) || (ch.unicode() <= 57 && ch.unicode() >= 48))) {
            QMessageBox::warning(this, "Ошибка", "ИКАО аэропорта отлёта должен содержать только заглавные латинские литеры и цифры");
            return;
        }
    }
    if (ui->arrivalAirport->text().size() != 4) {
        QMessageBox::warning(this, "Ошибка", "Код ИКАО аэропорта прилета должен содержать 4 символа");
        return;
    }
    for (QChar& ch : ui->arrivalAirport->text()) {
        if(!((ch.unicode() <= 90 && ch.unicode() >= 65) || (ch.unicode() <= 57 && ch.unicode() >= 48))) {
            QMessageBox::warning(this, "Ошибка", "ИКАО аэропорта прилёта должен содержать только заглавные латинские литеры и цифры");
            return;
        }
    }

    emit sentForm(ui->numberOfFlight->text(), ui->nameOfAirline->text(), ui->onBoardNumber->text(), ui->departureAirport->text(), ui->arrivalAirport->text());
    ui->numberOfFlight->clear();
    ui->nameOfAirline->clear();
    ui->onBoardNumber->clear();
    ui->departureAirport->clear();
    ui->arrivalAirport->clear();

    //QMessageBox::information(this, "Добавление", "Добавление прошло успешно!");

}

