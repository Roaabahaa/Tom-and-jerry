#include "leaderboard.h"
#include "ui_leaderboard.h"

LeaderBoard::LeaderBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LeaderBoard)
{
    QDir::setCurrent("C:/Users/moham/Desktop/Fall 2021/CS2/GameImages");
    QPixmap background("blackBackground.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);


    QVector<User> users;
    ui->setupUi(this);
    QFile file("C:/Users/moham/Desktop/Fall 2021/CS2/GameImages/leaderBoard.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList userData = line.split(" ");
        users.push_back(User(userData[0], userData[1].toInt()));
        //ui->listWidget->addItem(line);
    }

    mergeSort(users, 0, users.size()-1);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);
    for(QVector<User>::iterator i=users.begin(); i!=users.end(); i++)
    {
        QString line = i->getUsername() + " " + QString::number(i->getTime());
        ui->listWidget->addItem(line);
        stream << line << "\n";
    }
    file.close();
}

void LeaderBoard::addUser(User &account)
{
    int index = findUser(account);
    if(index == -1)
    {
        QFile file("C:/Users/moham/Desktop/Fall 2021/CS2/GameImages/leaderBoard.txt");
        if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        {
          // We're going to streaming text to the file
          QTextStream stream(&file);
          stream << account.getUsername() << " " << account.getTime() << "\n";
          file.close();
        }
    } else {
        updateUser(index, account.getTime());
    }
}

int LeaderBoard::findUser(User &account)
{
    QFile file("C:/Users/moham/Desktop/Fall 2021/CS2/GameImages/leaderBoard.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    int index = 0;
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList userData = line.split(" ");
        if(userData[0] == account.getUsername())
            return index;
        index++;
    }
    return -1;
}

void LeaderBoard::updateUser(int index, int time)
{
    QFile file("C:/Users/moham/Desktop/Fall 2021/CS2/GameImages/leaderBoard.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);
    QString output;
    int i = 0;
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList userData = line.split(" ");
        if(i==index)
        {
            output += userData[0] + " "  + QString::number(time) + "\n";
        } else {
            output += line + "\n";
        }
        i++;
    }
    file.close();

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      // We're going to streaming text to the file
      QTextStream stream(&file);
      stream << output;
      file.close();
    }
}

void LeaderBoard::mergeSort(QVector<User> &vec, int start, int end)
{
    if(start<end)
    {
        int middle = (start+end)/2;
        mergeSort(vec, start,middle);
        mergeSort(vec, middle+1,end);
        merge(vec, start,middle,end);
    }
}

void LeaderBoard::merge(QVector<User> &vec, int start, int middle, int end)
{
    int i = start;
    int j = middle+1;
    QVector<User> temp;

    while(i<=middle && j<=end)
    {
        if(vec[i]<vec[j])
        {
            temp.push_back(vec.at(i));
            i++;
        } else {
            temp.push_back(vec.at(j));
            j++;
        }
    }

    while(i<=middle)
    {
        temp.push_back(vec.at(i));
        i++;
    }

    while(j<=end)
    {
        temp.push_back(vec.at(j));
        j++;
    }

    int k = 0;
    for(QVector<User>::Iterator i = vec.begin()+start; i !=vec.begin()+end+1; i++)
    {
       *i = temp.at(k);
        k++;
    }
}

LeaderBoard::~LeaderBoard()
{
    delete ui;
}

void LeaderBoard::on_closeButton_clicked()
{
    hide();
}

