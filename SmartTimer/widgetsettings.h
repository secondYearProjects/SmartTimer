#ifndef WIDGETSETTINGS_H
#define WIDGETSETTINGS_H

#include <QString>
#include <QTime>



class WidgetSettings
{
public:
    WidgetSettings (const QString &_name);

private:
    QString name;
    int msecs;

    bool enabled; // Used for Alarms.
    bool days[7]; // Used to indicate if alsrm works on some days.

    QString signalPath;


};

struct GlobalSettings
{
public:
    GlobalSettings(double opacity=1.0 ,QString alarmFormat="HH:mm" ,QString timerFormat="HH:mm:ss"):
        windowOpacity(opacity), alarmTimeFormat(alarmFormat), timerTimeFormat(timerFormat) {}

    double windowOpacity=1.0;
    QString alarmTimeFormat = "HH:mm";
    QString timerTimeFormat = "HH:mm:ss";
};

#endif // WIDGETSETTINGS_H
