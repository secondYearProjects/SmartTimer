#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timerwidget.h"
#include "addtimerdialog.h"


#include <iostream>

#include <QListWidget>
#include <QtGlobal>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    logger = new smartTimerLog(this);

    connect(ui->addTimerButton, SIGNAL(clicked()), this, SLOT(addTimer()));
    // TODO : here
    connect(logger, SIGNAL(createTimer(int,QString)), this, SLOT(onTimeRecieved(int,QString)));

    scrollWidget = new QWidget;
    scrollWidget->setLayout(new QVBoxLayout);
    scrollWidget->setMaximumWidth(400);
    ui->timerScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    ui->timerScroll->setWidget(scrollWidget);

    //ui->alarmScroll->layout()->addWidget(new ToggleSwitch(this));

    logger->runLogger();
}

MainWindow::~MainWindow()
{
    emit del(this->timersList);

    delete ui;
}


void MainWindow::addTimer()
{
    auto *addDial = new addTimerDialog();
    connect(addDial,SIGNAL(sendTimerData(int,QString)),this, SLOT(onTimeRecieved(int,QString)));

    addDial->exec();
}

void MainWindow::onTimeRecieved(int msecs, const QString& _name)
{
    auto *newTimer = new TimerWidget(msecs, _name);

    scrollWidget->layout()->addWidget(newTimer);

    connect(newTimer, SIGNAL(del(const TimerWidget*)), this, SLOT(remove(const TimerWidget*)));
    connect(newTimer, SIGNAL(timerFinished()), this, SLOT(onTimerFinished()));

    timersList.append(newTimer);
}

void MainWindow::remove(const TimerWidget *twidget)
{
    if (std::find(timersList.begin(),timersList.end(),twidget) != timersList.end())
    {
        timersList.erase(std::find(timersList.begin(),timersList.end(),twidget));
    }
}

void MainWindow::onTimerFinished()
{

    // TODO: something here or give up
#ifdef Q_OS_LINUX
    system("notify-send 'Timer alert' '<b>Timer finished</b>' '-t' 5000");
    //system("notify-send '-i' '/home/sergei/work/SmartTimer/SmartTimer/icons/play-icon.png'");
#endif
}
