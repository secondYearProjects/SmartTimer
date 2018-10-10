#include "smarttimerlog.h"

#include <iostream>
#include <fstream>

#include <QTextStream>
#include <QUrl>
#include <QString>

smartTimerLog::smartTimerLog(QObject *parent) : QObject(parent)
{
    /*
    QFile logFile("ss.txt");
    if (!logFile.open(QIODevice::ReadOnly))
    {
        std::cerr << "Cannot open file." << std::endl;
        return;
    }*/

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

void smartTimerLog::saveLog()
{
    // TODO: here
}

bool smartTimerLog::validateLog()
{
    return true;
}
