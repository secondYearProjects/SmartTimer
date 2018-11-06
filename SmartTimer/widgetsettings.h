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
    GlobalSettings(double opacity=1.0 ,QString alarmFormat="HH:mm" ,QString timerFormat="HH:mm:ss", bool DDenable=false, int _DDstart=0, int _DDend=0):
        windowOpacity(opacity), alarmTimeFormat(alarmFormat), timerTimeFormat(timerFormat), DDenabled(DDenable), DDstart(_DDstart), DDend(_DDend) {}

    double windowOpacity=1.0;
    QString alarmTimeFormat = "HH:mm";
    QString timerTimeFormat = "HH:mm:ss";
    bool DDenabled = false;
    int DDstart = 0;
    int DDend = 0;

};

bool DDCheck(GlobalSettings globalSettings);
int elpasedTime(QTime time);

#endif // WIDGETSETTINGS_H
