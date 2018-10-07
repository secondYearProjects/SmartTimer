#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timerwidget.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTimer()
{
    auto *newTimer = new TimerWidget();
    ui->verticalLayout->addWidget(newTimer);
    std::cerr << newTimer->getID();
}
