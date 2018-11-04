#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timerwidget.h"
#include "addtimerdialog.h"
#include "addalarmdialog.h"
#include "alertwidget.h"
#include "globalsettingsdialog.h"


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
    Settings = GlobalSettings(1.0,"HH:mm","HH:mm:ss");

    connect(ui->addTimerButton,SIGNAL(clicked()),this,SLOT(addTimer()));
    connect(ui->addAlarmButton,SIGNAL(clicked()),this,SLOT(addAlarm()));
    connect(ui->settingsButton,SIGNAL(clicked()),this,SLOT(changeSettings()));

    connect(logger, SIGNAL(createTimer(int,QString)), this, SLOT(onTimeRecieved(int,QString)));
    connect(logger, SIGNAL(createAlarm(int,QString,bool)), this, SLOT(onAlarmTimeRecieved(int,QString,bool)));
    connect(logger, SIGNAL(createSettings(GlobalSettings)), this, SLOT(onSettingsRecieved(GlobalSettings)));


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

    this->setWindowOpacity(Settings.windowOpacity);
}

MainWindow::~MainWindow()
{
    emit del(this->timersList, this->alarmsList, this->Settings);

    delete ui;
}


void MainWindow::addTimer()
{
    auto *addDial = new addTimerDialog(this);
    connect(addDial,SIGNAL(sendTimerData(int,QString)),this, SLOT(onTimeRecieved(int,QString)));


    addDial->exec();
}

void MainWindow::addAlarm()
{
    auto *addDial = new addAlarmDialog(this);
    connect(addDial,SIGNAL(sendAlarmData(int,QString,bool)),this, SLOT(onAlarmTimeRecieved(int,QString,bool)));

    addDial->exec();
}

void MainWindow::changeSettings()
{
    GlobalSettingsDialog* dial = new GlobalSettingsDialog(this->Settings,this);

    connect(dial,SIGNAL(changeSettings(GlobalSettings)),this,SLOT(onSettingsRecieved(GlobalSettings)));

    dial->exec();

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

void MainWindow::onSettingsRecieved(GlobalSettings settings)
{
    Settings = settings;

    this->setWindowOpacity(Settings.windowOpacity);
}

// TODO: here
// update settings handler

void MainWindow::tabBlinking(QString tabName, bool enable)
{
    if (enable)
    {
        this->activateWindow();
        this->raise();
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

        ui->TimersBlink->setProperty("blink", false);
        ui->TimersBlink->style()->unpolish(ui->TimersBlink);
        ui->TimersBlink->style()->polish(ui->TimersBlink);
        ui->TimersBlink->update();;

        timersBlinkState = false;

        timersBlinking = false;

    }

    if (!blinkingAlarms)
    {
        alarmsBlinkTimer->stop();

        ui->AlarmsBlink->setProperty("blink", false);
        ui->AlarmsBlink->style()->unpolish(ui->AlarmsBlink);
        ui->AlarmsBlink->style()->polish(ui->AlarmsBlink);
        ui->AlarmsBlink->update();

        alarmsBlinkState = false;

        alarmsBlinking = false;
    }

}

void MainWindow::alarmsTabBlink()
{
    ui->AlarmsBlink->setProperty("blink", !alarmsBlinkState);
    ui->AlarmsBlink->style()->unpolish(ui->AlarmsBlink);
    ui->AlarmsBlink->style()->polish(ui->AlarmsBlink);
    ui->AlarmsBlink->update();

    alarmsBlinkState = !alarmsBlinkState;
}

void MainWindow::timersTabBlink()
{

    ui->TimersBlink->setProperty("blink", !timersBlinkState);
    ui->TimersBlink->style()->unpolish(ui->TimersBlink);
    ui->TimersBlink->style()->polish(ui->TimersBlink);
    ui->TimersBlink->update();



    timersBlinkState = !timersBlinkState;
}
