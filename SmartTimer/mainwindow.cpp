#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timerwidget.h"
#include "addtimerdialog.h"

#include <iostream>

#include <QListWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    logger = new smartTimerLog(this);

    connect(ui->addTimerButton, SIGNAL(clicked()), this, SLOT(addTimer()));
    // TODO : here
    connect(logger, SIGNAL(createTimer(int,const QString&)), this, SLOT(onTimeRecieved(int, const QString&)));

    scrollWidget = new QWidget;
    scrollWidget->setLayout(new QVBoxLayout);
    scrollWidget->setMaximumWidth(400);
    ui->timerScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    ui->timerScroll->setWidget(scrollWidget);

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
    connect(addDial,SIGNAL(sendTimerData(int, const QString&)),this, SLOT(onTimeRecieved(int, const QString&)));
    addDial->exec();
}

void MainWindow::onTimeRecieved(int msecs, const QString& _name)
{
    auto *newTimer = new TimerWidget(msecs, _name);

    scrollWidget->layout()->addWidget(newTimer);

    connect(newTimer, SIGNAL(del(const TimerWidget*)), this, SLOT(remove(const TimerWidget*)));

    timersList.append(newTimer);
}

void MainWindow::remove(const TimerWidget *twidget)
{
    if (std::find(timersList.begin(),timersList.end(),twidget) != timersList.end())
    {
        timersList.erase(std::find(timersList.begin(),timersList.end(),twidget));
    }
}
