#include "user.h"

const int User::ADMIN = 3;
const int User::MANAGER = 2;
const int User::SALESMAN = 1;

QString User::number = "";
QString User::username = "";
bool User::isLogined = false;
int User::level = -1;

User::User()
{

}

QString User::GetGender(int gender)
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

QString User::GetLevel(int level)
{
    switch (level) {
    case 1:
        return QString("Salesman");
    case 2:
        return QString("Manager");
    case 3:
        return QString("Admin");
    default:
        return QString("Unkonw");
    }
}
