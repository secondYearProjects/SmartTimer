// ref

#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H

#include "widgetsettings.h"


#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QSound>
#include <QMediaPlayer>
#include <QUrl>
#include <QMediaPlaylist>

namespace Ui {
class TimerWidget;
}

class TimerWidget : public QWidget
{
    Q_OBJECT

public:    
    explicit TimerWidget(WidgetSettings settings, QWidget *parent = nullptr);
    ~TimerWidget();

    int getID() { return id; }
    std::string getDurationString();
    std::string getTimeLeftString();

    QString getTimerName();
    int getTimerDuration();
    bool isRunning() {return this->timer->isActive(); }
    inline WidgetSettings getSettings() const {return this->Settings; }

    void setTimerName(const QString &_name);
    void setTimerDuration(int _duration);

    void updateWidget(GlobalSettings _globalSettings);

public slots:
    void startTimer();
    void resetTimer();
    void timerExecuted();
    void updateLeftTime();

    void changeTimer();

    void blink();
    void closeTimer();

    void setTimer(WidgetSettings _settings);
signals:
    void del(const TimerWidget* twidget);

    void timerFinished();

    void addBlink();
    void deleteBlink();

    void blinkInfo(QString tabName,bool enable);

private:
    static int MAXID;

    WidgetSettings Settings;
    GlobalSettings globalSettings;

    int id;
    QTimer *timer;
    QTimer *tickTimer;
    QTimer *blinkTimer;
    //QString name;
    //int duration;
    int timeLeft;
    bool blinky;

    QMediaPlaylist *playlist;
    QMediaPlayer *player;

    Ui::TimerWidget *ui;

    std::string secondsToTimeString(int val);


};


#endif // TIMERWIDGET_H
