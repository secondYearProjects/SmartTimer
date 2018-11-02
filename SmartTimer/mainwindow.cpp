#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timerwidget.h"
#include "addtimerdialog.h"
#include "addalarmdialog.h"
#include "alertwidget.h"


#include <iostream>

#include <QListWidget>
#include <QtGlobal>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QFile file(":/stylesheet.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->setStyleSheet(file.readAll());
        file.close();
    }


    logger = new smartTimerLog(this);
    alarmsBlinkTimer = new QTimer(this);
    timersBlinkTimer = new QTimer(this);

    connect(ui->addTimerButton,SIGNAL(clicked()),this,SLOT(addTimer()));
    connect(ui->addAlarmButton,SIGNAL(clicked()),this,SLOT(addAlarm()));

    connect(logger, SIGNAL(createTimer(int,QString)), this, SLOT(onTimeRecieved(int,QString)));
    connect(logger, SIGNAL(createAlarm(int,QString,bool)), this, SLOT(onAlarmTimeRecieved(int,QString,bool)));


    connect(alarmsBlinkTimer,SIGNAL(timeout()),this,SLOT(alarmsTabBlink()));
    connect(timersBlinkTimer,SIGNAL(timeout()),this,SLOT(timersTabBlink()));



    timerScrollWidget = new QWidget;
    timerScrollWidget->setLayout(new QVBoxLayout);
    timerScrollWidget->setMaximumWidth(400);
    ui->timerScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    ui->timerScroll->setWidget(timerScrollWidget);

    alarmScrollWidget = new QWidget;
    alarmScrollWidget->setLayout(new QVBoxLayout);
    alarmScrollWidget->setMaximumWidth(400);
    ui->alarmScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    ui->alarmScroll->setWidget(alarmScrollWidget);

    logger->runLogger();
}

MainWindow::~MainWindow()
{
    emit del(this->timersList, this->alarmsList);

    delete ui;
}


void MainWindow::addTimer()
{
    auto *addDial = new addTimerDialog();
    connect(addDial,SIGNAL(sendTimerData(int,QString)),this, SLOT(onTimeRecieved(int,QString)));


    addDial->exec();
}

void MainWindow::addAlarm()
{
    auto *addDial = new addAlarmDialog();
    connect(addDial,SIGNAL(sendAlarmData(int,QString,bool)),this, SLOT(onAlarmTimeRecieved(int,QString,bool)));

    addDial->exec();
}

void MainWindow::onTimeRecieved(int msecs, const QString& _name)
{
    auto *newTimer = new TimerWidget(msecs, _name);

    timerScrollWidget->layout()->addWidget(newTimer);

    connect(newTimer, SIGNAL(del(const TimerWidget*)), this, SLOT(remove(const TimerWidget*)));
    connect(newTimer, SIGNAL(timerFinished()), this, SLOT(onTimerFinished()));
    connect(newTimer, SIGNAL(blinkInfo(QString, bool)), this, SLOT(tabBlinking(QString,bool)));


    timersList.append(newTimer);
}

void MainWindow::remove(const TimerWidget *twidget)
{
    if (std::find(timersList.begin(),timersList.end(),twidget) != timersList.end())
    {
        timersList.erase(std::find(timersList.begin(),timersList.end(),twidget));
    }
}

void MainWindow::remove(const alertwidget *awidget)
{
    if (std::find(alarmsList.begin(),alarmsList.end(),awidget) != alarmsList.end())
    {
        alarmsList.erase(std::find(alarmsList.begin(),alarmsList.end(),awidget));
    }
}

void MainWindow::onTimerFinished()
{
#ifdef Q_OS_LINUX
    int sysRespond = system("notify-send 'Timer alert' '<b>Timer finished</b>' '-t' 5000");
    if (sysRespond)
        std::cerr << "Sys respond: " << sysRespond << std::endl;
#endif
}

void MainWindow::onAlarmTimeRecieved(int msecs, const QString& _name, bool turnedOn)
{
    auto *newAlarm = new alertwidget(msecs, _name, turnedOn);

    alarmScrollWidget->layout()->addWidget(newAlarm);

    connect(newAlarm, SIGNAL(del(const alertwidget*)), this, SLOT(remove(const alertwidget*)));
    connect(newAlarm, SIGNAL(blinkInfo(QString, bool)), this, SLOT(tabBlinking(QString,bool)));


    alarmsList.append(newAlarm);
}

void MainWindow::tabBlinking(QString tabName, bool enable)
{
    if (enable)
    {
        if (tabName=="Timers")
        {
            blinkingTimers++;
            ui->SmartTimerTabs->setCurrentIndex(0);
        }
        if (tabName=="Alarms")
        {
            blinkingAlarms++;
            ui->SmartTimerTabs->setCurrentIndex(1);
        }
    }
    else
    {
        if (tabName=="Timers" && blinkingTimers)
        {
            blinkingTimers--;
        }
        if (tabName=="Alarms" && blinkingAlarms)
        {
            blinkingAlarms--;
        }
    }
    if (blinkingTimers && !timersBlinking)
    {
        timersBlinkTimer->start(400);
        timersBlinking = true;
        timersBlinkState = false;
    }
    if (blinkingAlarms && !alarmsBlinking)
    {
        alarmsBlinkTimer->start(400);
        alarmsBlinking = true;
        alarmsBlinkState = false;
    }

    if (!blinkingTimers)
    {
        timersBlinkTimer->stop();

        ui->Timers->setProperty("blink", false);
        this->style()->unpolish(ui->Timers);
        this->style()->polish(ui->Timers);

        timersBlinkState = false;

        timersBlinking = false;

    }

    if (!blinkingAlarms)
    {
        alarmsBlinkTimer->stop();

        ui->Alarms->setProperty("blink", false);
        this->style()->unpolish(ui->Alarms);
        this->style()->polish(ui->Alarms);

        alarmsBlinkState = false;

        alarmsBlinking = false;
    }

}

void MainWindow::alarmsTabBlink()
{
    ui->Alarms->setProperty("blink", !alarmsBlinkState);
    ui->Alarms->style()->unpolish(ui->Alarms);
    ui->Alarms->style()->polish(ui->Alarms);


    alarmsBlinkState = !alarmsBlinkState;
}

void MainWindow::timersTabBlink()
{

    ui->Timers->setProperty("blink", !timersBlinkState);
    ui->Timers->style()->unpolish(ui->Timers);
    ui->Timers->style()->polish(ui->Timers);
    ui->Timers->update();



    timersBlinkState = !timersBlinkState;
}
