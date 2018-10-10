#include "timerwidget.h"
#include "ui_timerwidget.h"

#include "changetimerdialog.h"

#include <iostream>
#include <string>

int TimerWidget::MAXID = 0;

TimerWidget::TimerWidget( int _interval, const QString& _name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimerWidget)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    tickTimer = new QTimer(this);
    blinkTimer = new QTimer(this);

    duration = _interval;
    timeLeft = 0;
    name = _name;

    blinky = false;

    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/sound1.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    player = new QMediaPlayer();
    player->setPlaylist(playlist);


    ui->intervalTime->setText(QString::fromStdString(secondsToTimeString(duration/1000)));
    ui->timeLeft->setText(QString::fromStdString(secondsToTimeString(duration/1000)));
    ui->TimerName->setText(_name);

    connect(timer,SIGNAL(timeout()),this, SLOT(timerExecuted()));
    connect(tickTimer,SIGNAL(timeout()),this,SLOT(updateLeftTime()));
    connect(blinkTimer,SIGNAL(timeout()),this, SLOT(blink()));

    connect(ui->startButton, SIGNAL(clicked()),this, SLOT(startTimer()));
    connect(ui->restartButton, SIGNAL(clicked()),this, SLOT(resetTimer()));
    connect(ui->deleteTimerButton,SIGNAL(released()),this, SLOT(closeTimer()));

    connect(ui->editButton, SIGNAL(clicked()), this, SLOT(changeTimer()));




    ui->restartButton->setDisabled(true);
    ui->editButton->setEnabled(true);
    ui->startButton->setEnabled(true);

    id = MAXID+1;
    TimerWidget::MAXID++;

}

TimerWidget::~TimerWidget()
{
    delete ui;
}

QString TimerWidget::getTimerName()
{
    return name;
}

int TimerWidget::getTimerDuration()
{
    return duration;
}

void TimerWidget::setTimerName(const QString &_name)
{
    name = _name;
    ui->TimerName->setText(_name);
}

void TimerWidget::setTimerDuration(int _duration)
{
    duration = _duration;

    timer->stop();
    tickTimer->stop();

    ui->startButton->setEnabled(true);
    ui->editButton->setEnabled(true);
    ui->restartButton->setDisabled(true);

    ui->intervalTime->setText(QString::fromStdString(secondsToTimeString(duration/1000)));
    ui->timeLeft->setText(QString::fromStdString(secondsToTimeString(duration/1000)));
}

void TimerWidget::resetTimer()
{
    timer->stop();
    tickTimer->stop();
    blinkTimer->stop();


    if (player->state())
        player->stop();

    timeLeft = 0;
    ui->timeLeft->setText(QString::fromStdString(secondsToTimeString(duration/1000)));

    ui->restartButton->setDisabled(true);
    ui->startButton->setEnabled(true);
    ui->editButton->setEnabled(true);

    ui->restartButton->setStyleSheet("");
}

void TimerWidget::timerExecuted()
{
    //std::cerr << getID() << " " << "timer executed!";
    player->play();
    blinkTimer->start(350);

    timer->stop();
    tickTimer->stop();

    ui->timeLeft->setText(QString::fromStdString(secondsToTimeString(0)));
}

void TimerWidget::updateLeftTime()
{
    if(timeLeft >= 0)
    {
        std::string time = secondsToTimeString(timeLeft);
        ui->timeLeft->setText(QString::fromStdString(time));

        timeLeft--;
    }
}

void TimerWidget::changeTimer()
{
    ChangeTimerDialog *changeDial = new ChangeTimerDialog(this);

    changeDial->exec();
}

void TimerWidget::blink()
{
    if(blinky)
    {
        ui->restartButton->setStyleSheet("");

        blinky = false;
    }
    else
    {
        ui->restartButton->setStyleSheet("background-color: rgb(245, 121, 0)");
        blinky = true;
    }
}


void TimerWidget::closeTimer()
{
    player->stop();
    timer->stop();
    tickTimer->stop();
    blinkTimer->stop();

    emit del(this);

    this->close();
}



void TimerWidget::startTimer()
{
    timeLeft = duration/1000-1;
    tickTimer->start(1000);
    timer->start(duration);
    ui->startButton->setDisabled(true);
    ui->editButton->setDisabled(true);
    ui->restartButton->setEnabled(true);
}

std::string TimerWidget::secondsToTimeString(int val)
{
    int tmp = val/3600;
    std::string time = (tmp<10)?("0"+std::to_string(tmp)):std::to_string(tmp);
    time+=":";
    tmp = (val%3600)/60;
    time += (tmp<10)?("0"+std::to_string(tmp)):std::to_string(tmp);
    time+=":";
    tmp = val%60;
    time += (tmp<10)?("0"+std::to_string(tmp)):std::to_string(tmp);

    return time;
}
