#include "timer.h"

Timer::Timer():
    QObject(), timer(new QTimer()), interval(QTime(0,0,0)), isPaused(false)
{

}

Timer::Timer(QTime timeInterval):
    QObject(), timer(new QTimer()), interval(timeInterval), isPaused(false)
{

}

Timer::~Timer()
{
    stop();
    delete timer;
}

void Timer::start()
{
    timer->start(interval.elapsed());
}

void Timer::stop()
{
    timer->stop();
}

void Timer::pause()
{
    pausePassed = timer->remainingTime();
}

