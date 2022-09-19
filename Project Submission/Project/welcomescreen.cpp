#include "welcomescreen.h"
#include "ui_welcomescreen.h"

WelcomeScreen::WelcomeScreen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WelcomeScreen)
{
    ui->setupUi(this);
    QDir::setCurrent("C:/Users/moham/Desktop/Fall 2021/CS2/GameImages");
    QPixmap background("welcomeScreen.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

}

WelcomeScreen::~WelcomeScreen()
{
    delete ui;
}


void WelcomeScreen::on_playButton_clicked()
{
    if(!ui->nameText->text().isEmpty())
    {
        User account;
        account.setUsername(ui->nameText->text());
        GameScreen* screen = new GameScreen(ui->difficulty->currentIndex(), ui->spinBox->value(), account);
        screen->show();
        hide();
    } else {
        QMessageBox msgBox;
        msgBox.setText("ERROR: Username cannot be empty!");
        msgBox.exec();
    }
}

