#ifndef ADDFLIGHTMODAL_H
#define ADDFLIGHTMODAL_H

#include <QDialog>

namespace Ui {
class addFlightModal;
}

class addFlightModal : public QDialog
{
    Q_OBJECT

public:
    explicit addFlightModal(QWidget *parent = nullptr);
    ~addFlightModal();

private:
    Ui::addFlightModal *ui;
};

#endif // ADDFLIGHTMODAL_H
