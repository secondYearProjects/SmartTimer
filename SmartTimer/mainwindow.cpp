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
    connect(addDial,SIGNAL(sendTime(int)),this, SLOT(onTimeRecieved(int)));
    addDial->exec();


}

void MainWindow::onTimeRecieved(int msecs)
{
    auto *newTimer = new TimerWidget(msecs);

    ui->verticalLayout->addWidget(newTimer);
    std::cerr << newTimer->getID();
}
