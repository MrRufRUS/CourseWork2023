#ifndef SEARCHMODAL_H
#define SEARCHMODAL_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class searchModal;
}

class searchModal : public QDialog
{
    Q_OBJECT

public:
    explicit searchModal(QWidget *parent = nullptr);
    ~searchModal();

private slots:
    void on_find_clicked();

    void on_cancel_clicked();
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

signals:
    void sentSearchedData(int, QVector<QString>);
public slots:
    void recieveDataToSeacrh(QVector<QVector<QString>>& dataToSearch);
private:
    Ui::searchModal *ui;
    QVector<QVector<QString>> dts;
    QString stringToSearch;
    int col = -1;
};

#endif // SEARCHMODAL_H
