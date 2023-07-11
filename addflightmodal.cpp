#include "addflightmodal.h"
#include "ui_addflightmodal.h"

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
