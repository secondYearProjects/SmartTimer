#include "globalsettingsdialog.h"
#include "ui_globalsettingsdialog.h"
#include "rangewidget.h"
#include "widgetsettings.h"

#include <QFile>
#include <QSlider>
#include <QHBoxLayout>



GlobalSettingsDialog::GlobalSettingsDialog(GlobalSettings old, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GlobalSettingsDialog)
{
    ui->setupUi(this);

    QFile file(":/stylesheet.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->setStyleSheet(file.readAll());
        file.close();
    }

    oldSettings = old;

    ui->opacitySlider->setValue(static_cast<int>(old.windowOpacity*100));
    ui->SliderValue->setText(QString::number(static_cast<int>(old.windowOpacity*100))+"%");
    ui->alarmFormat->setText(old.alarmTimeFormat);
    ui->TimerFormat->setText(old.timerTimeFormat);

    if (oldSettings.DDenabled)
        ui->DDenable->setChecked(true);

    if (!oldSettings.DDenabled)
    {
        ui->DDmin->setEnabled(false);
        ui->DDmax->setEnabled(false);
    }

    ui->DDmin->setTime(QTime::fromMSecsSinceStartOfDay(oldSettings.DDstart));
    ui->DDmax->setTime(QTime::fromMSecsSinceStartOfDay(oldSettings.DDend));

    connect(ui->DDenable,SIGNAL(clicked(bool)),this, SLOT(DDenableState(bool)));

    //RangeWidget *DDrange = new RangeWidget(Qt::Horizontal);
    //ui->RangeLayout->addWidget(DDrange);

    //connect(DDrange,SIGNAL(rangeChanged(int , int )),this,SLOT(rangeChanged(int,int)));


    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(canceled()));
    connect(ui->confirmButton,SIGNAL(clicked()),this, SLOT(confirmed()));
    connect( ui->opacitySlider,SIGNAL(valueChanged(int)),this,SLOT(opacityChanged()));

}

GlobalSettingsDialog::~GlobalSettingsDialog()
{
    delete ui;
}

void GlobalSettingsDialog::confirmed()
{
    int elpasedTimeMin = elpasedTime(ui->DDmin->time());
    int elpasedTimeMax = elpasedTime(ui->DDmax->time());
    GlobalSettings newSettings(ui->opacitySlider->value()/100.0,
                               ui->alarmFormat->text(),
                               ui->TimerFormat->text(),
                               static_cast<bool>(ui->DDenable->isChecked()),
                               elpasedTimeMin,
                               elpasedTimeMax);
    emit changeSettings(newSettings);
    this->close();
}

void GlobalSettingsDialog::canceled()
{
    emit changeSettings(oldSettings);
    this->close();
}

void GlobalSettingsDialog::opacityChanged()
{
    int elpasedTimeMin = elpasedTime(ui->DDmin->time());
    int elpasedTimeMax = elpasedTime(ui->DDmax->time());
    GlobalSettings newSettings(ui->opacitySlider->value()/100.0,ui->alarmFormat->text(), ui->TimerFormat->text(),static_cast<bool>(ui->DDenable->isChecked()),elpasedTimeMin, elpasedTimeMax);

    ui->SliderValue->setText(QString::number(static_cast<int>(newSettings.windowOpacity*100))+"%");

    emit changeSettings(newSettings);
}

void GlobalSettingsDialog::rangeChanged(int min, int max)
{
    ui->RangeValue->setText(QString::number(min)+" : "+QString::number(max));
}

void GlobalSettingsDialog::DDenableState(bool state)
{
        ui->DDmin->setEnabled(state);
        ui->DDmax->setEnabled(state);

}


