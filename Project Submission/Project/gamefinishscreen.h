#ifndef GAMEFINISHSCREEN_H
#define GAMEFINISHSCREEN_H

#include <QMainWindow>
#include <QPixmap>
#include <QDir>
#include "welcomescreen.h"
#include "leaderboard.h"

namespace Ui {
class GameFinishScreen;
}

class GameFinishScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameFinishScreen(bool win, QWidget *parent = nullptr);
    ~GameFinishScreen();

private slots:
    void on_playAgainButton_clicked();

    void on_leaderBoardButton_clicked();

private:
    Ui::GameFinishScreen *ui;
};

#endif // GAMEFINISHSCREEN_H
