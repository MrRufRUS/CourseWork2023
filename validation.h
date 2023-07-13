#ifndef VALIDATION_H
#define VALIDATION_H
#include <QRegularExpression>
#include <QString>
#include <QDebug>


inline bool validateData(const QString& data)
{
    // Создаем регулярное выражение для проверки наличия только заглавных английских букв и цифр
    QRegularExpression regex("^[A-Z0-9-]*$");

    // Создаем объект соответствия регулярному выражению
    QRegularExpressionMatch match = regex.match(data);

    // Проверяем, есть ли соответствие
    if (match.hasMatch())
    {
        return true; // Данные соответствуют требованиям
    }
    else
    {
        return false; // Данные не соответствуют требованиям
    }
}
inline bool validateASCII(const QString& data)
{
    // Создаем регулярное выражение для проверки наличия только символов ASCII
    QRegularExpression regex("^[\\x00-\\x7F]*$");

    // Создаем объект соответствия регулярному выражению
    QRegularExpressionMatch match = regex.match(data);

    // Проверяем, есть ли соответствие
    if (match.hasMatch())
    {
        return true; // Данные соответствуют требованиям ASCII-таблицы
    }
    else
    {
        return false; // Данные не соответствуют требованиям ASCII-таблицы
    }
}

#endif // VALIDATION_H
