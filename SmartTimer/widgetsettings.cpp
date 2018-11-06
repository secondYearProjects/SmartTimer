#include "widgetsettings.h"

void addSounds(QComboBox *soundsCombo)
{
    soundsCombo->addItem("Standard signal", "qrc:/sounds/sound1.wav");
    soundsCombo->addItem("Bird", "qrc:/sounds/Bird.mp3");
    soundsCombo->addItem("Light", "qrc:/sounds/Light.mp3");
}
