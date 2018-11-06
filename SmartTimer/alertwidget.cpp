#include "alertwidget.h"
#include "ui_alertwidget.h"
#include "changealarmdialog.h"

#include <iostream>

int getMsecs(const QTime& t)
{
    return (t.hour()*3600+t.minute()*60+t.second())*1000;
}

int calculateDuration(const QTime &t)
{
    int alertMsecs = getMsecs(t);
    int currMsecs = getMsecs(QTime::currentTime());

    if (currMsecs > alertMsecs)
    {
        int wholeDay = 3600*24*1000;
        return (wholeDay+alertMsecs-currMsecs);
    }
    else if (currMsecs < alertMsecs)
    {
        return (alertMsecs-currMsecs);
    }
    else
        return 0;
}

alertwidget::alertwidget(WidgetSettings settings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alertwidget)
{
    Settings = settings;

    alertTime = QTime::fromMSecsSinceStartOfDay(Settings.msecs);

    blinking = false;
    blinky=false;

    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl(Settings.signalPath));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    player = new QMediaPlayer();
    player->setPlaylist(playlist);


    ui->setupUi(this);

    QFile file(":/stylesheet.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->setStyleSheet(file.readAll());
        file.close();
    }

    ui->timeLabel->setText(alertTime.toString(globalSettings.alarmTimeFormat));
    ui->alarmNameLabel->setText(Settings.name);

    ui->alertSwitch->setStatus(Settings.enabled);

    ui->stopButton->hide();

    connect(ui->alertSwitch, SIGNAL(statusChanged(bool)),this, SLOT(statusChanged(bool)));
    connect(&alertTick, SIGNAL(timeout()), this, SLOT(onTickCheck()));
    connect(&blinkTimer, SIGNAL(timeout()),this,SLOT(blink()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stopBlinking()));


    if (Settings.enabled)
    {
        std::cout << calculateDuration(alertTime) << " "
                  << QTime::currentTime().hour() <<":" << QTime::currentTime().minute() << std::endl;
        alertTick.start(calculateDuration(alertTime));
    }


    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(customContextMenuRequest(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));

}

alertwidget::~alertwidget()
{
    player->stop();

    delete ui;
}

int alertwidget::getAlertTime()
{
    return getMsecs(this->alertTime);
}


void alertwidget::statusChanged(bool stat)
{
    Settings.enabled = stat;
    if (stat)
    {

        std::cout << calculateDuration(alertTime) << " "
                  << QTime::currentTime().hour() <<":" << QTime::currentTime().minute() << std::endl;
        alertTick.start(calculateDuration(alertTime));
    }
    else
    {
        if (blinkTimer.isActive())
            emit blinkInfo("Alarms",false);

        alertTick.stop();
        blinkTimer.stop();
        blinking = false;
        ui->widget->setStyleSheet("QWidget { background-color: rgb(113,113,113); }");
        player->stop();
        ui->stopButton->hide();
    }
}


void alertwidget::onTickCheck()
{
    std::cout << "!alert!" << std::endl;
    alertTick.stop();
    blinkTimer.start(300);
    blinking = true;
    player->play();
    ui->stopButton->show();
    ui->stopButton->setEnabled(true);

    emit blinkInfo("Alarms",true);
}

void alertwidget::blink()
{
    if (blinky)
    {
        ui->widget->setStyleSheet("QWidget {"
                                  " background-color: qlineargradient(spread:pad, x1:0.622, y1:0.0113636,"
                                  " x2:1, y2:0, stop:0 rgb(183, 106, 56), stop:0.626368 rgba(0, 0, 0, 0));"
                                  " border-radius: 30px;"
                                  " border: 0px;"
                                  " }");
    }
    else
    {
        ui->widget->setStyleSheet("QWidget {"
                                  " background-color: rgb(113,113,113);"
                                  " border: 0px; "
                                  "}");
    }
    blinky = !blinky;
}

void alertwidget::stopBlinking()
{
    if (blinkTimer.isActive())
        emit blinkInfo("Alarms",false);

    alertTick.stop();
    blinkTimer.stop();
    blinking = false;
    ui->widget->setStyleSheet("QWidget { background-color: rgb(113,113,113); }");
    player->stop();
    ui->stopButton->hide();
    if (Settings.enabled)
    {
        std::cout << calculateDuration(alertTime) << " "
                  << QTime::currentTime().hour() <<":" << QTime::currentTime().minute() << std::endl;
        alertTick.start(calculateDuration(alertTime));
    }
}

void alertwidget::closeAlarm()
{
    if (blinkTimer.isActive())
        emit blinkInfo("Alarms",false);

    alertTick.stop();
    blinkTimer.stop();
    player->stop();


    emit del(this);


    this->close();
}

void alertwidget::changeAlarm()
{
    ChangeAlarmDialog *dial = new ChangeAlarmDialog(this);

    connect(dial, SIGNAL(changeAlarmSignal(WidgetSettings)),this,SLOT(setAlarm(WidgetSettings)));

    dial->updateWidget(globalSettings);
    dial->exec();
}

void alertwidget::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);

    QAction actionDelete("Delete alarm", this);
    QAction actionChange("Change alarm", this);

    connect(&actionDelete, SIGNAL(triggered()), this, SLOT(closeAlarm()));
    connect(&actionChange, SIGNAL(triggered()), this, SLOT(changeAlarm()));
    contextMenu.addAction(&actionDelete);
    contextMenu.addAction(&actionChange);

    contextMenu.exec(mapToGlobal(pos));

}

void alertwidget::setAlarm(WidgetSettings settings)
{
    Settings = settings;

    ui->timeLabel->setText(QTime::fromMSecsSinceStartOfDay(Settings.msecs).toString(globalSettings.alarmTimeFormat));
    ui->alarmNameLabel->setText(Settings.name);

    alertTime = QTime::fromMSecsSinceStartOfDay(Settings.msecs);

    playlist->clear();
    playlist->addMedia(QUrl(Settings.signalPath));

    statusChanged(true);

}

void alertwidget::updateWidget(GlobalSettings _globalSettings)
{
    globalSettings = _globalSettings;
    ui->timeLabel->setText((QTime::fromMSecsSinceStartOfDay(Settings.msecs)).toString(globalSettings.alarmTimeFormat));

}


void alertwidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton && !blinkTimer.isActive())
    {
        player->stop();
        ShowContextMenu(e->pos());
    }
}

