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
