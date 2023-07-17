#ifndef SHOWHASHFUNCTION_H
#define SHOWHASHFUNCTION_H

#include <QDialog>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QTextBrowser>

namespace Ui {
class ShowHashFunction;
}

class ShowHashFunction : public QDialog
{
    Q_OBJECT

public:
    explicit ShowHashFunction(QWidget *parent = nullptr);
    ~ShowHashFunction();

private slots:
    void on_show_clicked();

    void on_close_clicked();

private:
    Ui::ShowHashFunction *ui;
};

#endif // SHOWHASHFUNCTION_H
