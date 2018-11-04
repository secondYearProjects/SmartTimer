#pragma once

#include "smarttimerlog.h"
#include "timerwidget.h"
#include "alertwidget.h"
#include "widgetsettings.h"

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    GlobalSettings getSettings() {return Settings; }

    double getOpacity() { return Settings.windowOpacity; }
    QString getAlarmFormat() {return Settings.alarmTimeFormat; }
    QString getTimerFormat() {return Settings.timerTimeFormat; }

    void setSettings(GlobalSettings val) { Settings = val; this->update(); }

    void setOpacity(double val) { Settings.windowOpacity = val; this->update();}
    void setAlarmFormat(QString val) {Settings.alarmTimeFormat = val; this->update();}
    void setTimerFormat(QString val) {Settings.timerTimeFormat = val; this->update();}

    GlobalSettings getSettings() const { return Settings; }

public slots:
    void addTimer();
    void addAlarm();
    void changeSettings();
    void onTimeRecieved(WidgetSettings settings);
    void remove(const TimerWidget* twidget);
    void remove(const alertwidget* awidget);
    void onTimerFinished();
    void onAlarmTimeRecieved(WidgetSettings settings);
    void onSettingsRecieved(GlobalSettings settings);


    void tabBlinking(QString tabName, bool enable);
    void alarmsTabBlink();
    void timersTabBlink();


    void updateWidgets();

signals:
    void del(QList<TimerWidget*> timers,QList<alertwidget*> alarms,GlobalSettings);
private:
    Ui::MainWindow *ui;

    smartTimerLog* logger;

    QList<TimerWidget*> timersList;
    QList<alertwidget*> alarmsList;

    QWidget *timerScrollWidget;
    QWidget *alarmScrollWidget;

    int blinkingAlarms = 0;
    int blinkingTimers = 0;

    bool alarmsBlinking = false;
    bool timersBlinking = false;

    bool alarmsBlinkState = false;
    bool timersBlinkState = false;

    QTimer *alarmsBlinkTimer;
    QTimer *timersBlinkTimer;

    GlobalSettings Settings;

};

