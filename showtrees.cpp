#include "showtrees.h"
#include "ui_showtrees.h"

ShowTrees::ShowTrees(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowTrees)
{
    ui->setupUi(this);
}

ShowTrees::~ShowTrees()
{
    delete ui;
}

void ShowTrees::on_close_clicked()
{
    this->close();
}


void ShowTrees::on_tree0_clicked()
{
    QFile fin("avl0.txt");
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&fin);
    QString buffer;
    if(fin.isOpen()) {
        buffer = in.readAll();
        ui->trees->setText(buffer);
    }
    fin.close();
}


void ShowTrees::on_tree1_clicked()
{
    QFile fin("avl1.txt");
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&fin);
    QString buffer;
    if(fin.isOpen()) {
        buffer = in.readAll();
        ui->trees->setText(buffer);
    }
    fin.close();
}


void ShowTrees::on_tree2_clicked()
{
    QFile fin("avl2.txt");
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&fin);
    QString buffer;
    if(fin.isOpen()) {
        buffer = in.readAll();
        ui->trees->setText(buffer);
    }
    fin.close();
}


void ShowTrees::on_tree3_clicked()
{
    QFile fin("avl3.txt");
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&fin);
    QString buffer;
    if(fin.isOpen()) {
        buffer = in.readAll();
        ui->trees->setText(buffer);
    }
    fin.close();
}


void ShowTrees::on_tree4_clicked()
{
    QFile fin("avl4.txt");
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&fin);
    QString buffer;
    if(fin.isOpen()) {
        buffer = in.readAll();
        ui->trees->setText(buffer);
    }
    fin.close();
}

