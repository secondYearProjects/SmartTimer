#ifndef SMARTTIMERLOG_H
#define SMARTTIMERLOG_H

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
    void saveLog();

private:
    QString filePath = "saves/save.txt";

    bool validateLog();

};

#endif // SMARTTIMERLOG_H
