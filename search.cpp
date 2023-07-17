#include "search.h"
#include "ui_search.h"

search::search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::search)
{
    ui->setupUi(this);
}

search::~search()
{
    delete ui;
}

void search::on_pushButton_2_clicked()
{
    this->close();
}


void search::on_pushButton_clicked()
{

}

