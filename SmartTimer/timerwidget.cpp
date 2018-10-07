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

    connect(timer,SIGNAL(timeout()),this, SLOT(timerExecuted()));
    connect(ui->startButton, SIGNAL(clicked()),this, SLOT(startTimer()));
    connect(ui->restartButton, SIGNAL(clicked()),this, SLOT(setDuration()));
    connect(tickTimer,SIGNAL(timeout()),this,SLOT(updateLeftTime()));

    tickTimer->start(1000);

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
}

void TimerWidget::updateLeftTime()
{
    int remaining = timer->remainingTime()/1000;
    std::string time = std::to_string(remaining/3600) + ":" +
            std::to_string((remaining%3600)/60)+ ":" +
            std::to_string(remaining%60);
    ui->timeLeft->setText(QString::fromStdString(time));
}

void TimerWidget::startTimer()
{
    timer->start(duration);
}
