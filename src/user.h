#ifndef USER_H
#define USER_H

#include <QDebug>

class User
{
public:
    const static int ADMIN;
    const static int MANAGER;
    const static int SALESMAN;
    const static int UNKONW;

    static QString username;
    static QString number;
    static bool isLogined;
    static int level;
    User();

    static QString GetGender(const int gender);
    static QString GetLevel(const int level);
    static int GetLevel(const QString &level);
};

#endif // USER_H
