#include "smarttimerlog.h"
#include "timerwidget.h"

#include <iostream>
#include <fstream>

#include <QTextStream>
#include <QUrl>
#include <QString>

smartTimerLog::smartTimerLog(QObject *parent) : QObject(parent)
{
    this->par = parent;
    connect(par, SIGNAL(del(QList<TimerWidget*>)), this, SLOT(saveLog(QList<TimerWidget*>)));

}

void smartTimerLog::runLogger()
{
    int tim;
    std::string tmpstr;
    QString str;

    QFile logFile("save.txt");
    if (!logFile.open(QIODevice::ReadOnly))
    {
        // std::cerr << "Can't open log file." << std::endl;
        return;
    }
    if (!validateLog())
    {
        std::cerr << "Log file is broken." << std::endl;
        return;
    }

    QTextStream stream( &logFile );
    while(!stream.atEnd())
    {
        stream >> tim >> str;
        if (str != "")
            emit createTimer(tim,str);
    }


    logFile.close();
}

void smartTimerLog::saveLog(QList<TimerWidget*> timers)
{

    int tim;
    std::string tmpstr;
    QString str;

    QFile logFile("save.txt");

    if (!logFile.open(QIODevice::WriteOnly))
    {
        std::cerr << "Log file can't be created.";
    }

    QTextStream stream( &logFile );
    for (auto timer : timers)
    {
        tim = timer->getTimerDuration();
        str = timer->getTimerName();
        stream << tim << " " << str << "\n";
    }


    logFile.close();
}

// TODO: validator
bool smartTimerLog::validateLog()
{
    return true;
}
