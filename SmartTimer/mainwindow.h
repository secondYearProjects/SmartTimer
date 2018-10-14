#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "smarttimerlog.h"
#include "timerwidget.h"
#include "alertwidget.h"

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


public slots:
    void addTimer();
    void addAlarm();
    void onTimeRecieved(int msecs, const QString& _name);
    void remove(const TimerWidget* twidget);
    void onTimerFinished();
    void onAlarmTimeRecieved(int msecs, const QString& _name);

signals:
    void del(QList<TimerWidget*> timers);
private:
    Ui::MainWindow *ui;

    smartTimerLog* logger;

    QList<TimerWidget*> timersList;
    QList<alertwidget*> alarmsList;

    QWidget *timerScrollWidget;
    QWidget *alarmScrollWidget;
};

#endif // MAINWINDOW_H
