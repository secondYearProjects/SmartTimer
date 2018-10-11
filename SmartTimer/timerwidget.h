#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H


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
    explicit TimerWidget(int _interval, const QString &_name, QWidget *parent = nullptr);
    ~TimerWidget();

    int getID() { return id; }
    std::string getDurationString();
    std::string getTimeLeftString();

    QString getTimerName();
    int getTimerDuration();

    void setTimerName(const QString &_name);
    void setTimerDuration(int _duration);

public slots:
    void startTimer();
    void resetTimer();
    void timerExecuted();
    void updateLeftTime();

    void changeTimer();

    void blink();

    void closeTimer();
signals:
    void del(const TimerWidget* twidget);

    void timerFinished();

private:
    static int MAXID;

    int id;
    QTimer *timer;
    QTimer *tickTimer;
    QTimer *blinkTimer;
    QString name;
    int duration;
    int timeLeft;
    bool blinky;

    QMediaPlaylist *playlist;
    QMediaPlayer *player;

    Ui::TimerWidget *ui;

    std::string secondsToTimeString(int val);
};


#endif // TIMERWIDGET_H
