#ifndef SMARTTIMERLOG_H
#define SMARTTIMERLOG_H

#include "timerwidget.h"

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
public slots:
    void saveLog(QList<TimerWidget*> timers);

private:
    QString filePath = "saves/save.txt";

    QObject* par;

    bool validateLog();

};

#endif // SMARTTIMERLOG_H
