#ifndef TIMER_H
#define TIMER_H

#include <QTimer>
#include <QTime>
#include <QObject>

class Timer: public QObject
{
    Q_OBJECT
public:
    Timer();

    Timer(QTime timeInterval);

    ~Timer();

public slots:
    void start();
    void stop();
    void pause();
signals:
    void timerStarted();
    void timerStoped();
    void timerPaused();

    void ring();

private:
    QTimer* timer;
    QTime interval;
    QTime started;
    int pausePassed = 0;
    bool isPaused;
};

#endif // TIMER_H
