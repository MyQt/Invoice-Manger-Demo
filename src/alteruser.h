#ifndef ALTERUSER_H
#define ALTERUSER_H

#include <QDebug>

class AlterUser
{
public:
    AlterUser();
    static QString number;
    static QString name;
    static QString password;
    static QString gender;
    static QString phone;
    static QString email;
    static QString employedDate;
    static QString address;
    static QString level;
    static QString ps;
    static bool isAltered;
};

#endif // ALTERUSER_H
