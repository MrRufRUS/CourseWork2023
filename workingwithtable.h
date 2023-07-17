#ifndef WORKINGWITHTABLE_H
#define WORKINGWITHTABLE_H

#include <QString>
#include <QTableWidget>
#include <QString>
#include <QFile>

bool checkRepeat(QTableWidget*& table, QString& s0, int column) {
    for(int i = 0; i < table->rowCount(); i ++) {
        if(table->item(i, column)->text() == s0) {
            return false;
        }
    }
    return true;
}
void addNode(QTableWidget*& table, QString& s0, QString& s1, QString& s2, QString& s3, QString& s4) {
    table->insertRow(table->rowCount());
    table->setItem(table->rowCount()-1, 0, new QTableWidgetItem(s0));
    table->setItem(table->rowCount()-1, 1, new QTableWidgetItem(s1));
    table->setItem(table->rowCount()-1, 2, new QTableWidgetItem(s2));
    table->setItem(table->rowCount()-1, 3, new QTableWidgetItem(s3));
    table->setItem(table->rowCount()-1, 4, new QTableWidgetItem(s4));
}
void addNode(QTableWidget*& table, QVector<QString> d) {
    table->insertRow(table->rowCount());
    table->setItem(table->rowCount()-1, 0, new QTableWidgetItem(d.at(0)));
    table->setItem(table->rowCount()-1, 1, new QTableWidgetItem(d.at(1)));
    table->setItem(table->rowCount()-1, 2, new QTableWidgetItem(d.at(2)));
    table->setItem(table->rowCount()-1, 3, new QTableWidgetItem(d.at(3)));
    table->setItem(table->rowCount()-1, 4, new QTableWidgetItem(d.at(4)));
}



#endif // WORKINGWITHTABLE_H
