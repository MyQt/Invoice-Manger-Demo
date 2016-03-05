#ifndef USER_H
#define USER_H

#include <QDebug>

class User
{
public:
    const static int ADMIN;
    const static int MANAGER;
    const static int SALESMAN;

    static QString username;
    static QString number;
    static bool isLogined;
    static int level;
    User();
};

#endif // USER_H
