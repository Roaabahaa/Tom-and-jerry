#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User();
    User(QString name, int t);
    QString getUsername();
    void setUsername(QString name);
    int getTime();
    void setTime(int t);
    bool operator<(User &rhs);
    bool operator>(User &rhs);

private:
    QString username;
    int time;
};

#endif // USER_H
