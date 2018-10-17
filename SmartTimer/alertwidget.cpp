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

alertwidget::alertwidget(int msecs, const QString& name, bool turnedOn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alertwidget)
{
    alertName = name;
    alertTime = QTime::fromMSecsSinceStartOfDay(msecs);
    state = turnedOn;
    blinking = false;
    blinky=false;

    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/sound1.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    player = new QMediaPlayer();
    player->setPlaylist(playlist);


    ui->setupUi(this);

    ui->timeLabel->setText(alertTime.toString("hh:mm"));
    ui->alarmNameLabel->setText(alertName);

    ui->alertSwitch->setStatus(state);

    ui->stopButton->hide();

    connect(ui->alertSwitch, SIGNAL(statusChanged(bool)),this, SLOT(statusChanged(bool)));
    connect(&alertTick, SIGNAL(timeout()), this, SLOT(onTickCheck()));
    connect(&blinkTimer, SIGNAL(timeout()),this,SLOT(blink()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stopBlinking()));


    if (state)
    {
        std::cout << calculateDuration(alertTime) << " "
                  << QTime::currentTime().hour() <<":" << QTime::currentTime().minute() << std::endl;
        alertTick.start(calculateDuration(alertTime));
    }


    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
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
    state = stat;
    if (stat)
    {

        std::cout << calculateDuration(alertTime) << " "
                  << QTime::currentTime().hour() <<":" << QTime::currentTime().minute() << std::endl;
        alertTick.start(calculateDuration(alertTime));
    }
    else
    {
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
}

void alertwidget::blink()
{
    //TODO: here
    if (blinky)
    {
        ui->widget->setStyleSheet("QWidget {"
                                  " background-color: qlineargradient(spread:pad, x1:0.622, y1:0.0113636,"
                                  " x2:1, y2:0, stop:0 rgb(183, 106, 56), stop:0.626368 rgba(0, 0, 0, 0));"
                                  " border-radius: 30px;"
                                  " }");
    }
    else
    {
        ui->widget->setStyleSheet("QWidget { background-color: rgb(113,113,113); }");
    }
    blinky = !blinky;
}

void alertwidget::stopBlinking()
{
    alertTick.stop();
    blinkTimer.stop();
    blinking = false;
    ui->widget->setStyleSheet("QWidget { background-color: rgb(113,113,113); }");
    player->stop();
    ui->stopButton->hide();
    if (state)
    {
        std::cout << calculateDuration(alertTime) << " "
                  << QTime::currentTime().hour() <<":" << QTime::currentTime().minute() << std::endl;
        alertTick.start(calculateDuration(alertTime));
    }
}

void alertwidget::closeAlarm()
{
    alertTick.stop();
    blinkTimer.stop();
    player->stop();


    emit del(this);

    this->close();
}

void alertwidget::changeAlarm()
{
    ChangeAlarmDialog *dial = new ChangeAlarmDialog(this);

    connect(dial, SIGNAL(changeAlarmSignal(int,QString)),this,SLOT(setAlarm(int,QString)));

    dial->exec();
}

void alertwidget::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);

    QAction action1("Delete alarm", this);
    QAction action2("Change alarm", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(closeAlarm()));
    connect(&action2, SIGNAL(triggered()), this, SLOT(changeAlarm()));
    contextMenu.addAction(&action1);
    contextMenu.addAction(&action2);

    contextMenu.exec(mapToGlobal(pos));
}

void alertwidget::setAlarm(int msecs, const QString & _name)
{
    ui->timeLabel->setText(QTime::fromMSecsSinceStartOfDay(msecs).toString("hh:mm"));
    ui->alarmNameLabel->setText(_name);

    alertTime = QTime::fromMSecsSinceStartOfDay(msecs);
    alertName = _name;

    statusChanged(true);

}


void alertwidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton)
    {
        player->stop();

        ShowContextMenu(e->pos());
        //emit closeAlarm();
    }
}

