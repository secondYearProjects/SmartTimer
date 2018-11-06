#ifndef WIDGETSETTINGS_H
#define WIDGETSETTINGS_H

#include <QString>
#include <QTime>

#include <QComboBox>

void addSounds(QComboBox* soundsCombo);


struct WidgetSettings
{
public:
    WidgetSettings (int _msecs=0, const QString &_name="", bool _enabled=true, const QString &_path="qrc:/sounds/sound1.wav"):
        msecs(_msecs), name(_name), enabled(_enabled), signalPath(_path)
    {
    }

    int msecs;
    QString name;
    bool enabled; // Used for Alarms.

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
