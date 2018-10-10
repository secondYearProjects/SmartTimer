#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "smarttimerlog.h"
#include "timerwidget.h"

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
    void onTimeRecieved(int msecs, const QString& _name);
    void remove(const TimerWidget* twidget);

signals:
    void del(QList<TimerWidget*> timers);
private:
    Ui::MainWindow *ui;

    smartTimerLog* logger;

    QList<TimerWidget*> timersList;

    QWidget *scrollWidget;
};

#endif // MAINWINDOW_H
