#include "widgetsettings.h"
#include <QLineEdit>
#include <QTime>

void addSounds(QComboBox *soundsCombo)
{
    soundsCombo->addItem("Standard signal", "qrc:/sounds/sound1.wav");
    soundsCombo->addItem("Bird song", "qrc:/sounds/Bird.mp3");
    soundsCombo->addItem("Light music", "qrc:/sounds/Light.mp3");
}

int elpasedTime(QTime time)
{
    return time.hour()*3600*1000+
                time.minute()*60*1000+
                time.second()*1000;
}

bool DDCheck(GlobalSettings globalSettings)
{
    int currTime = elpasedTime(QTime::currentTime());

    if (globalSettings.DDenabled)
    {
        if (globalSettings.DDstart==globalSettings.DDend)
            return true;
        if(globalSettings.DDstart<globalSettings.DDend)
        {
            if (currTime>=globalSettings.DDstart && currTime <= globalSettings.DDend )
                return false;

            return true;
        }
        else
        {
            if (currTime>=globalSettings.DDstart || currTime <= globalSettings.DDend)
                return false;
            return true;
        }
    }
    else
        return true;

}

int calculateDuration(const QTime &t)
{
    int alertMsecs = getMsecs(t);
    int currMsecs = getMsecs(QTime::currentTime());

    if (currMsecs > alertMsecs)
    {
        int wholeDay = 3600*24*1000;
        return (wholeDay+alertMsecs-currMsecs);
    }
    if (currMsecs < alertMsecs)
    {
        return (alertMsecs-currMsecs);
    }
    return 0;
}

int getMsecs(const QTime &t)
{
    return (t.hour()*3600+t.minute()*60+t.second())*1000+t.msec();
}
