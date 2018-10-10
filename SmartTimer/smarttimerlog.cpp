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

    QFile logFile(":/saves/save.txt");
    if (!logFile.open(QIODevice::ReadOnly))
    {
        std::cerr << "Cannot open file." << std::endl;
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
        emit createTimer(tim,str);
    }


    logFile.close();
}

void smartTimerLog::saveLog(QList<TimerWidget*> timers)
{
    // TODO: here

    int tim;
    std::string tmpstr;
    QString str;

    QFile logFile(":/saves/save.txt");

    if (!logFile.open(QFile::WriteOnly))
    {
        std::cerr << "Cannot open file." << std::endl;
        return;
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

bool smartTimerLog::validateLog()
{
    return true;
}
