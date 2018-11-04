#include "globalsettingsdialog.h"
#include "ui_globalsettingsdialog.h"

#include <QFile>
#include <QSlider>

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

    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->confirmButton,SIGNAL(clicked()),this, SLOT(confirmed()));
    connect( ui->opacitySlider,SIGNAL(valueChanged(int)),this,SLOT(opacityChanged()));

}

GlobalSettingsDialog::~GlobalSettingsDialog()
{
    delete ui;
}

void GlobalSettingsDialog::confirmed()
{
    GlobalSettings newSettings(ui->opacitySlider->value()/100.0,ui->alarmFormat->text(), ui->TimerFormat->text());
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
    GlobalSettings newSettings(ui->opacitySlider->value()/100.0,ui->alarmFormat->text(), ui->TimerFormat->text());

    ui->SliderValue->setText(QString::number(static_cast<int>(newSettings.windowOpacity*100))+"%");

    emit changeSettings(newSettings);
}
