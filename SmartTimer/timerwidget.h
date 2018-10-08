#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTime>

namespace Ui {
class TimerWidget;
}

class TimerWidget : public QWidget
{
    Q_OBJECT

public:    
    explicit TimerWidget(QWidget *parent = nullptr);
    ~TimerWidget();

    int getID() { return id; }
    std::string getDurationString();
    std::string getTimeLeftString();

public slots:
    void startTimer();
    void setDuration();
    void timerExecuted();
    void updateLeftTime();
private:
    static int MAXID;

    int id;
    QTimer *timer;
    QTimer *tickTimer;
    int duration;
    int timeLeft;

    Ui::TimerWidget *ui;

    std::string secondsToTimeString(int val);
};


#endif // TIMERWIDGET_H
