#include "alertwidget.h"
#include "ui_alertwidget.h"

#include <iostream>

int getMsecs(const QTime& t)
{
    return (t.hour()*3600+t.minute()*60+t.second())*1000;
}

alertwidget::alertwidget(int msecs, const QString& name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alertwidget)
{
    alertName = name;
    alertTime = QTime::fromMSecsSinceStartOfDay(msecs);
    state = false;
    blinking = false;
    blinky=false;

    ui->setupUi(this);

    ui->timeLabel->setText(alertTime.toString("hh:mm"));
    ui->alarmNameLabel->setText(alertName);

    ui->alertSwitch->setStatus(state);

    connect(ui->alertSwitch, SIGNAL(statusChanged(bool)),this, SLOT(statusChanged(bool)));
    connect(&alertTick, SIGNAL(timeout()), this, SLOT(onTickCheck()));
    connect(&blinkTimer, SIGNAL(timeout()),this,SLOT(blink()));
}

alertwidget::~alertwidget()
{
    delete ui;
}

int alertwidget::getAlertTime()
{
    return getMsecs(alertTime)/1000;
}

void alertwidget::statusChanged(bool stat)
{
    state = stat;
    if (stat)
        alertTick.start(1000);
    else
    {
        alertTick.stop();
        blinkTimer.stop();
        blinking = false;
    }
}


void alertwidget::onTickCheck()
{

    if (abs(getMsecs(QTime::currentTime())- getMsecs(alertTime)) < 2000)
    {
        std::cout << "!alert!" << std::endl;
        alertTick.stop();
        blinkTimer.start(300);
        blinking = true;

    }
    else
        std::cout << "tick" << abs(getMsecs(QTime::currentTime())- getMsecs(alertTime)) << std::endl;
}

void alertwidget::blink()
{
    //TODO: here
    if (blinky)
    {

        ui->widget->setStyleSheet("QWidget { background-color: black; }");
    }
    else
    {
        ui->widget->setStyleSheet("QWidget { background-color: white; }");
    }
    blinky = !blinky;
}
