#ifndef ADDFLIGHTMODAL_H
#define ADDFLIGHTMODAL_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QAbstractButton>

namespace Ui {
class addFlightModal;
}

class addFlightModal : public QDialog
{
    Q_OBJECT

public:
    explicit addFlightModal(QWidget *parent = nullptr);
    ~addFlightModal();

private slots:
    void on_cancelButton_clicked();

    void on_addButton_clicked();

private:
    Ui::addFlightModal *ui;
signals:
    void sentForm(QString , QString, QString, QString, QString);
};

#endif // ADDFLIGHTMODAL_H
