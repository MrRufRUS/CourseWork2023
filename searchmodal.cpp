#include "searchmodal.h"
#include "ui_searchmodal.h"
#include "validation.h"

searchModal::searchModal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchModal)
{
    ui->setupUi(this);
}

searchModal::~searchModal()
{
    delete ui;
}
template<typename T>
QVector<QVector<T>> naturalMergeSort(QVector<QVector<T>>& a, int size, int& col);
template<typename T>
void merge(QVector<QVector<T>>& A, int const startPos, int const nA, int const nB,
           QVector<QVector<T>>& C, int& col);
int binarySearch(QVector<QVector<QString>>& nums,int low, int high, QString& target, int& steps, int& col);
void searchModal::on_find_clicked()
{
    switch (col) {
    case 0:
        {
            if (ui->lineEdit->text().size() < 5) {
                QMessageBox::warning(this, "Ошибка", "Номер рейса должен содержать минимум 5 символов");
                return;
            }
            if(!validateData(ui->lineEdit->text())) {
                QMessageBox::warning(this, "Ошибка", "Номер рейса должен содержать только заглавные латинские литеры, цифры и \"-\"");
                return;
            }
            stringToSearch = ui->lineEdit->text();
            break;
        }
    case 1:
        {
            if (ui->lineEdit_2->text().size() == 0) {
                QMessageBox::warning(this, "Ошибка", "Название авиакомпании не может быть пустым");
                return;
            }
            if(!validateASCII(ui->lineEdit_2->text()))
            {
                QMessageBox::warning(this, "Ошибка", "Введено неверное название авиакомпанни");
                return;
            }
            stringToSearch = ui->lineEdit_2->text();
            break;
        }
    case 2:
        {
            if (ui->lineEdit_3->text().size() == 0) {
                QMessageBox::warning(this, "Ошибка", "Бортовой номер не может быть пустым");
                return;
            }
            if(!validateData(ui->lineEdit_3->text())) {
                QMessageBox::warning(this, "Ошибка", "Бортовой номер должен содержать только заглавные латинские литеры, цифры и \"-\"");
                return;
            }
            stringToSearch = ui->lineEdit_3->text();
            break;
        }
    case 3:
        {
            if (ui->lineEdit_4->text().size() != 4) {
                QMessageBox::warning(this, "Ошибка", "Код ИКАО аэропорта вылета должен содержать 4 символа");
                return;
            }
            for (QChar& ch : ui->lineEdit_4->text()) {
                if(!((ch.unicode() <= 90 && ch.unicode() >= 65) || (ch.unicode() <= 57 && ch.unicode() >= 48))) {
                    QMessageBox::warning(this, "Ошибка", "ИКАО аэропорта отлёта должен содержать только заглавные латинские литеры и цифры");
                    return;
                }
            }
            stringToSearch = ui->lineEdit_4->text();
            break;
        }
    case 4:
        {
            if (ui->lineEdit_5->text().size() != 4) {
                QMessageBox::warning(this, "Ошибка", "Код ИКАО аэропорта прилета должен содержать 4 символа");
                return;
            }
            for (QChar& ch : ui->lineEdit_5->text()) {
                if(!((ch.unicode() <= 90 && ch.unicode() >= 65) || (ch.unicode() <= 57 && ch.unicode() >= 48))) {
                    QMessageBox::warning(this, "Ошибка", "ИКАО аэропорта прилёта должен содержать только заглавные латинские литеры и цифры");
                    return;
                }
            }
            stringToSearch = ui->lineEdit_5->text();
            break;
        }
    default:
        break;
    }

    int steps = 0;

    auto dtssor = naturalMergeSort(dts, dts.size(), col);
    int pos = binarySearch(dtssor, 0, dtssor.size(), stringToSearch, steps, col);
    qDebug() << dtssor[pos][0] <<" "<<dtssor[pos][1] <<" "<<dtssor[pos][2] <<" "<<dtssor[pos][3]  << "\n";
}

void searchModal::on_cancel_clicked()
{
    this->close();
}

void searchModal::recieveDataToSeacrh(QVector<QVector<QString>>& dataToSearch)
{
    dts = dataToSearch;
}


void searchModal::on_radioButton_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit->setDisabled(false);
    ui->lineEdit_2->setDisabled(true);
    ui->lineEdit_3->setDisabled(true);
    ui->lineEdit_4->setDisabled(true);
    ui->lineEdit_5->setDisabled(true);
    col = 0;
    ui->find->setDisabled(false);
}


void searchModal::on_radioButton_2_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit->setDisabled(true);
    ui->lineEdit_2->setDisabled(false);
    ui->lineEdit_3->setDisabled(true);
    ui->lineEdit_4->setDisabled(true);
    ui->lineEdit_5->setDisabled(true);
    col = 1;
    ui->find->setDisabled(false);
}


void searchModal::on_radioButton_3_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit->setDisabled(true);
    ui->lineEdit_2->setDisabled(true);
    ui->lineEdit_3->setDisabled(false);
    ui->lineEdit_4->setDisabled(true);
    ui->lineEdit_5->setDisabled(true);
    col = 2;
    ui->find->setDisabled(false);
}


void searchModal::on_radioButton_4_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit->setDisabled(true);
    ui->lineEdit_2->setDisabled(true);
    ui->lineEdit_3->setDisabled(true);
    ui->lineEdit_4->setDisabled(false);
    ui->lineEdit_5->setDisabled(true);
    col = 3;
    ui->find->setDisabled(false);
}

void searchModal::on_radioButton_5_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit->setDisabled(true);
    ui->lineEdit_2->setDisabled(true);
    ui->lineEdit_3->setDisabled(true);
    ui->lineEdit_4->setDisabled(true);
    ui->lineEdit_5->setDisabled(false);
    col = 4;
    ui->find->setDisabled(false);
}
template<typename T>
void merge(QVector<QVector<T>>& A, int const startPos, int const nA, int const nB,
           QVector<QVector<T>>& C, int& col)
{ //Выполнить слияние массива A, содержащего nA элементов,
    //  и массива B, содержащего nB элементов.
    //  Результат записать в массив C.

    int a = startPos, b = startPos; //Номера текущих элементов в массивах A и B
    int bb = nA;
    //std::cout << startPos << " " << nA << " " << nB << "\n";
    while (a + b - (startPos * 2) < nA + nB) //Пока остались элементы в массивах
    {
        //std::cout << a << " " << b + bb << "\n";
        if ((b - startPos >= nB) || ((a - startPos < nA) && A[a][col] <= A[b + bb][col]))
        { //Копирую элемент из массива A
                //std::cout << A[a] << std::endl;
                C.push_back(A[a]);
                ++a;
        }
        else { //Копирую элемент из массива B
                //std::cout << A[b + bb] << std::endl;
                C.push_back(A[b + bb]);
                ++b;
        }
    }

}
template<typename T>
QVector<QVector<T>> naturalMergeSort(QVector<QVector<T>>& a, int size, int& col) {
    QVector<QVector<T>> b = {};
    int start1, end1, start2, end2;
    do {


        start2 = -1;
        end2 = -1;
        do {

                start1 = end2 + 1; end1 = start1;

                while (end1 < size - 1 && a[end1][col] <= a[end1 + 1][col])
                    end1++;

                if (end1 != size - 1) { //break;

                    start2 = end1 + 1;
                    end2 = start2;

                    while (end2 < size - 1 && a[end2][col] <= a[end2 + 1][col])
                        end2++;

                    merge<T>(a, start1, end1 - start1 + 1, end2 - start2 + 1, b, col);
                }

        } while (end1 != size - 1 && end2 != size - 1);
        //if (start1 == 0 && end1 == size - 1)
        //break;
        if (start1 != 0 && end1 == size - 1) {
                for (; start1 < size; start1++)
                    b.push_back(a[start1]);
                return b;
        }
        else if (start1 != 0 || end1 != size - 1) {
                return b;
        }
    } while (start1 != 0 || end1 != size - 1);
}

int binarySearch(QVector<QVector<QString>>& nums,int low, int high, QString& target, int& steps, int& col)
{
    steps++;

    // Базовое условие (пространство поиска исчерпано)
    if (low > high) {
        return -1;
    }

    // находим среднее значение в пространстве поиска и
    // сравнивает его с целью

    int mid = (low + high) / 2;    // может произойти переполнение
    // int mid = low + (high - low)/2;

    // Базовое условие (найдено целевое значение)
    if (target == nums[mid][col]) {
        while (target == nums[mid + 1][col])
                mid++;
        return mid;
    }

    // отбросить все элементы в правильном пространстве поиска,
    // включая средний элемент
    else if (target < nums[mid][col]) {
        return binarySearch(nums, low, mid - 1, target, steps, col);
    }

    // отбрасываем все элементы в левой области поиска,
    // включая средний элемент
    else {
        return binarySearch(nums, mid + 1, high, target, steps, col);
    }
}
