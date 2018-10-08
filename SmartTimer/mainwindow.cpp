#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timerwidget.h"
#include "addtimerdialog.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->addTimerButton, SIGNAL(clicked()), this, SLOT(addTimer()));
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

    ui->verticalLayout->addWidget(newTimer);
    std::cerr << newTimer->getID();
}
