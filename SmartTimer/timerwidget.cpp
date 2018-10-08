#include "timerwidget.h"
#include "ui_timerwidget.h"

#include <iostream>
#include <string>

int TimerWidget::MAXID = 0;

TimerWidget::TimerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimerWidget)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    tickTimer = new QTimer(this);
    duration = 5000;
    timeLeft = 0;

    ui->intervalTime->setText(QString::fromStdString(secondsToTimeString(duration/1000)));

    connect(timer,SIGNAL(timeout()),this, SLOT(timerExecuted()));
    connect(ui->startButton, SIGNAL(clicked()),this, SLOT(startTimer()));
    connect(ui->restartButton, SIGNAL(clicked()),this, SLOT(setDuration()));
    connect(tickTimer,SIGNAL(timeout()),this,SLOT(updateLeftTime()));
    connect(ui->deleteTimerButton,SIGNAL(released()),this, SLOT(close()));

    id = MAXID+1;
    TimerWidget::MAXID++;

}

TimerWidget::~TimerWidget()
{
    delete ui;
}

void TimerWidget::setDuration()
{
    duration = 0;
}

void TimerWidget::timerExecuted()
{
    std::cerr << getID() << " " << "timer executed!";
    timer->stop();
    tickTimer->stop();

    ui->timeLeft->setText("00:00:00");

    ui->startButton->setEnabled(true);
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

void TimerWidget::startTimer()
{
    timeLeft = duration/1000-1;
    tickTimer->start(1000);
    timer->start(duration);
    ui->startButton->setDisabled(true);
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
