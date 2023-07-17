#ifndef SHOWTREES_H
#define SHOWTREES_H

#include <QDialog>
#include <QFile>

namespace Ui {
class ShowTrees;
}

class ShowTrees : public QDialog
{
    Q_OBJECT

public:
    explicit ShowTrees(QWidget *parent = nullptr);
    ~ShowTrees();

private slots:
    void on_close_clicked();

    void on_tree0_clicked();

    void on_tree1_clicked();

    void on_tree2_clicked();

    void on_tree3_clicked();

    void on_tree4_clicked();

private:
    Ui::ShowTrees *ui;
};

#endif // SHOWTREES_H
