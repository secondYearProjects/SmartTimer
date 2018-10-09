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

    connect(ui->addTimerButton, SIGNAL(clicked()), this, SLOT(addTimer()));

    scrollWidget = new QWidget;
    scrollWidget->setLayout(new QVBoxLayout);
    scrollWidget->setMaximumWidth(400);
    ui->timerScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    ui->timerScroll->setWidget(scrollWidget);
}

MainWindow::~MainWindow()
{
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

    //ui->timersList->addWidget(newTimer);
    //ui->verticalLayout->addWidget(newTimer);
    std::cerr << newTimer->getID();
}
