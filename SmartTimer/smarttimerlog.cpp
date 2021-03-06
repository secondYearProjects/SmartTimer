#include "smarttimerlog.h"
#include "timerwidget.h"
#include "widgetsettings.h"
#include "widgetsettings.h"

#include <iostream>
#include <fstream>

#include <QTextStream>
#include <QUrl>
#include <QString>

#include <QJsonDocument>

smartTimerLog::smartTimerLog(QObject *parent) : par(parent)
{
    this->par = parent;
    connect(par, SIGNAL(del(QList<TimerWidget*>,QList<alertwidget*>,GlobalSettings)), this, SLOT(saveLog(QList<TimerWidget*>,QList<alertwidget*>,GlobalSettings)));

}

void smartTimerLog::runLogger()
{
    int tim;
    std::string tmpstr;
    QString str;
    bool turned;
    int boolTmp;
    QString signalPath;

    QFile logFile("save.txt");
    if (!logFile.exists())
        return;
    if (!logFile.open(QIODevice::ReadOnly))
    {
        // std::cerr << "Can't open log file." << std::endl;
        return;
    }

    QTextStream stream( &logFile );
    while(!stream.atEnd())
    {
        stream >> tim >> str >> signalPath;

        if (str != "")
        {
            str = toLoadFormat(str);
            emit createTimer(WidgetSettings(tim,str,true,toLoadFormat(signalPath)));
        }
    }


    logFile.close();

    // alarm part
    QFile logFile2("saveA.txt");
    if (!logFile2.exists())
        return;
    if (!logFile2.open(QIODevice::ReadOnly))
    {
        // std::cerr << "Can't open log file." << std::endl;
        return;
    }

    QTextStream stream2( &logFile2 );

    while(!stream2.atEnd())
    {
        stream2 >> tim >> str >> boolTmp >> signalPath;
        turned = boolTmp;
        if (str != "")
        {
            str = toLoadFormat(str);

            emit createAlarm(WidgetSettings(tim,str,turned,toLoadFormat(signalPath)));
        }
    }

    logFile2.close();

    // global settings

    QFile logFile3("saveSettings.txt");
    if (!logFile3.exists())
        return;
    if (!logFile3.open(QIODevice::ReadOnly))
    {
        // std::cerr << "Can't open log file." << std::endl;
        return;
    }

    QTextStream stream3( &logFile3 );
    double opacity;
    QString alarmFormat;
    QString timerFormat;
    int DDenable;
    int DDmin;
    int DDmax;
    stream3 >> opacity >> alarmFormat >> timerFormat >> DDenable >> DDmin >> DDmax;
    emit createSettings(GlobalSettings(opacity,toLoadFormat(alarmFormat), toLoadFormat(timerFormat),static_cast<bool>(DDenable),DDmin,DDmax));


    logFile3.close();
}

void smartTimerLog::saveLog(QList<TimerWidget*> timers, QList<alertwidget*> alarms, GlobalSettings settings)
{

    int tim;
    std::string tmpstr;
    QString str;
    bool turned;
    QString signalPath;

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
        str = toSaveFormat(str);
        signalPath = toSaveFormat(timer->getSettings().signalPath);
        stream << tim << " " << str << " " << signalPath <<  " \n";
    }


    logFile.close();

    // alarm part
    QFile logFile2("saveA.txt");

    if (!logFile2.open(QIODevice::WriteOnly))
    {
        std::cerr << "Log file can't be created.";
    }

    QTextStream stream2( &logFile2 );
    for (auto alarm : alarms)
    {
        tim = alarm->getAlertTime();
        str = alarm->getName();
        turned = alarm->getState();
        signalPath = toSaveFormat(alarm->getSettings().signalPath);
        str = toSaveFormat(str);
        stream2 << tim << " " << str << " " << static_cast<int>(turned) << " " << signalPath << " \n";
    }

    logFile2.close();


    // Global settings
    QFile logFile3("saveSettings.txt");
    if (!logFile3.open(QIODevice::WriteOnly))
    {
        std::cerr << "Log file can't be created.";
    }

    QTextStream stream3( &logFile3 );

    stream3 << settings.windowOpacity << " \n";
    stream3 << toSaveFormat(settings.alarmTimeFormat) << " \n";
    stream3 << toSaveFormat(settings.timerTimeFormat) << " \n";
    stream3 << settings.DDenabled << " " << settings.DDstart << " " << settings.DDend << " \n";

    logFile3.close();
}


QString smartTimerLog::toLoadFormat(const QString &str)
{
    if (str == "&")
        return "";
    QString res = str;
    res.replace("*"," ");
    return res;
}

QString smartTimerLog::toSaveFormat(const QString &str)
{
    if (str == "")
        return "&";
    QString res = str;
    res.replace(" ","*");
    return res;
}
