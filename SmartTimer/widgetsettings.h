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

#endif // WIDGETSETTINGS_H
