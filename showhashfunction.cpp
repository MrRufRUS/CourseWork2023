#include "showhashfunction.h"
#include "ui_showhashfunction.h"

ShowHashFunction::ShowHashFunction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowHashFunction)
{
    ui->setupUi(this);
}

ShowHashFunction::~ShowHashFunction()
{
    delete ui;
}

void ShowHashFunction::on_show_clicked()
{
    QFile fin("hashtable.txt");
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&fin);
    QString buffer;
    if(fin.isOpen()) {
        buffer = in.readAll();
        ui->hashtable->setText(buffer);
    }
    fin.close();
}


void ShowHashFunction::on_close_clicked()
{
    this->close();
}

