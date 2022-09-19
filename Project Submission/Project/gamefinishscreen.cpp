#include "gamefinishscreen.h"
#include "ui_gamefinishscreen.h"

GameFinishScreen::GameFinishScreen(bool win, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameFinishScreen)
{
    ui->setupUi(this);
    QDir::setCurrent("C:/Users/moham/Desktop/Fall 2021/CS2/GameImages");
    QPixmap background;
    if(win)
    {
        setWindowTitle("Congratulations! You Win!");
        background =  QPixmap("winScreen.jpg");
    }
    else
    {
        setWindowTitle("OH OH! You Lose!");
        background = QPixmap("loseScreen.jpg");
    }
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);
}

GameFinishScreen::~GameFinishScreen()
{
    delete ui;
}

void GameFinishScreen::on_playAgainButton_clicked()
{
    WelcomeScreen* screen = new WelcomeScreen();
    screen->show();
    hide();
}


void GameFinishScreen::on_leaderBoardButton_clicked()
{
    LeaderBoard* screen = new LeaderBoard();
    screen->show();
}

