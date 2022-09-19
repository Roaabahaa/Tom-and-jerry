#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <QMainWindow>
#include <QPixmap>
#include <QDir>
#include <QMessageBox>
#include <gamescreen.h>



QT_BEGIN_NAMESPACE
namespace Ui { class WelcomeScreen; }
QT_END_NAMESPACE


class WelcomeScreen : public QMainWindow
{
    Q_OBJECT

public:
    WelcomeScreen(QWidget *parent = nullptr);
    ~WelcomeScreen();

private slots:
    void on_playButton_clicked();

private:
    Ui::WelcomeScreen *ui;
};
#endif // WELCOMESCREEN_H
