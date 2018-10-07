#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QLayout>
#include <QtGui>
#include <QtCore>
#include <QLabel>

#include <vector>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QGridLayout *layout = new QGridLayout;

    std::vector<QLabel*> labelVec;
    for (int i =0;i<10;i++)
    {
        labelVec.push_back(new QLabel("Hello"));
        layout->addWidget(labelVec[static_cast<unsigned int>(i)], i, i%4);
    }
    this->setLayout(layout);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
