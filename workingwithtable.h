#ifndef WORKINGWITHTABLE_H
#define WORKINGWITHTABLE_H

#include <QString>
#include <QTableWidget>
#include <QString>
#include <QFile>
#include "validation.h"

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

void parser(QString name, QTableWidget*& table, QVector<QVector<QString>>& data) {
    QFile fin(name);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
//    while(!fin.atEnd()) {
//        QString str = fin.getLine;
//        QString list = str.split(";");
//        if (list.at(0).size() < 5) {
//            return;
//        }
//        if(!validateData(list.at(0))) {
//            return;
//        }
//        if (list.at(1).size() == 0) {
//            return;
//        }
//        if(!validateASCII(list.at(1)))
//        {
//            return;
//        }
//        if (list.at(2).size() == 0) {
//            return;
//        }
//        if(!validateData(list.at(2))) {
//            return;
//        }
//        if (list.at(3).size() != 4) {
//            return;
//        }
//        for (QChar& ch : list.at(3)) {
//            if(!((ch.unicode() <= 90 && ch.unicode() >= 65) || (ch.unicode() <= 57 && ch.unicode() >= 48))) {
//                return;
//            }
//        }
//        if (list.at(4).size() != 4) {
//            return;
//        }
//        for (QChar& ch : list.at(4)) {
//            if(!((ch.unicode() <= 90 && ch.unicode() >= 65) || (ch.unicode() <= 57 && ch.unicode() >= 48))) {
//                return;
//            }
//        }
//    }

}


#endif // WORKINGWITHTABLE_H
