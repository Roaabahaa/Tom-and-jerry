#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVector>
#include <QPixmap>
#include <QFile>
#include <QDir>
#include "user.h"

namespace Ui {
class LeaderBoard;
}

class LeaderBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit LeaderBoard(QWidget *parent = nullptr);
    static void addUser(User &account);
    static int findUser(User &account);
    static void updateUser(int index, int time);
    void mergeSort(QVector<User> &vec, int start, int end);
    void merge(QVector<User> &vec, int start, int middle, int end);
    ~LeaderBoard();

private slots:
    void on_closeButton_clicked();

private:
    Ui::LeaderBoard *ui;
};

#endif // LEADERBOARD_H
