#ifndef SMARTTIMERLOG_H
#define SMARTTIMERLOG_H

#include "timerwidget.h"
#include "alertwidget.h"

#include <QObject>
#include <QString>
#include <QFile>

class smartTimerLog : public QObject
{
    Q_OBJECT
public:
    explicit smartTimerLog(QObject *parent = nullptr);
    void runLogger();

signals:
    void createTimer(int duration, const QString& timerName);
    void createAlarm(int msecs, const QString &alarmName, bool turnedOn);
public slots:
    void saveLog(QList<TimerWidget*> timers, QList<alertwidget*> alarms);

private:

    QObject* par;

    bool validateLog();
    QString toLoadFormat(const QString& str);
    QString toSaveFormat(const QString& str);

};

#endif // SMARTTIMERLOG_H
