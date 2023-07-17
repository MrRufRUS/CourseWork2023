#ifndef SEARCH_H
#define SEARCH_H

#include <QWidget>

namespace Ui {
class search;
}

class search : public QWidget
{
    Q_OBJECT

public:
    explicit search(QWidget *parent = nullptr);
    ~search();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
signals:
    void sentSearchedData(QVector<int>, QVector<QVector<QString>>);
private:
    Ui::search *ui;
};

#endif // SEARCH_H
