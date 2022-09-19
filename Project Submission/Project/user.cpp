#include "user.h"

User::User()
{}

User::User(QString name, int t)
{
    username = name;
    time = t;
}

QString User::getUsername()
{
    return username;
}

void User::setUsername(QString name)
{
    username = name;
}

void User::setTime(int t)
{
    time = t;
}

int User::getTime()
{
    return time;
}

bool User::operator<(User &rhs)
{
    return this->time < rhs.time;
}
bool User::operator>(User &rhs)
{
    return this->time > rhs.time;
}


