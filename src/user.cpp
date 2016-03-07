#include "user.h"

const int User::ADMIN = 3;
const int User::MANAGER = 2;
const int User::SALESMAN = 1;
const int User::UNKONW = -1;

QString User::number = "";
QString User::username = "";
bool User::isLogined = false;
int User::level = -1;

User::User()
{

}

QString User::GetGender(const int gender)
{
    switch (gender) {
    case 0:
        return QString("Man");
    case 1:
        return QString("Woman");
    default:
        return QString("Unknow");
    }
}

QString User::GetLevel(const int level)
{
    switch (level) {
    case SALESMAN:
        return QString("Salesman");
    case MANAGER:
        return QString("Manager");
    case ADMIN:
        return QString("Admin");
    default:
        return QString("Unkonw");
    }
}

int User::GetLevel(const QString &level)
{
    if (level == QString("ADMIN")) {
        return ADMIN;
    }
    if (level == QString("MANAGER")) {
        return MANAGER;
    }
    if (level == QString("SALESMAN")) {
        return SALESMAN;
    }
    return UNKONW;
}
