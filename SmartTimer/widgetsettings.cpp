#include "widgetsettings.h"
#include <QLineEdit>
#include <QTime>

void addSounds(QComboBox *soundsCombo)
{
    soundsCombo->addItem("Standard signal", "qrc:/sounds/sound1.wav");
    soundsCombo->addItem("Bird", "qrc:/sounds/Bird.mp3");
    soundsCombo->addItem("Light", "qrc:/sounds/Light.mp3");
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
    if (currTime>=globalSettings.DDstart && currTime <= globalSettings.DDend )
        return false;
    else
        return true;
}
