#ifndef ALERTWIDGET_H
#define ALERTWIDGET_H

#include "widgetsettings.h"

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QSound>
#include <QMediaPlayer>
#include <QUrl>
#include <QMediaPlaylist>

namespace Ui {
class alertwidget;
}

class alertwidget : public QWidget
{
    Q_OBJECT

public:
    explicit alertwidget(WidgetSettings settings, QWidget *parent = nullptr);
    ~alertwidget();

    inline bool getState() { return Settings.enabled; }
    inline QString getName() {return Settings.name; }
    int getAlertTime();

public slots:
    void statusChanged(bool);
    void onTickCheck();
    void blink();
    void stopBlinking();
    void closeAlarm();

    void changeAlarm();

    void ShowContextMenu(const QPoint &);

    void setAlarm(WidgetSettings settings);

    void updateWidget(GlobalSettings _globalSettings);

signals:
    void alarmFinished();
    void del(const alertwidget*);

    void customContextMenuRequest(const QPoint &);

    void blinkInfo(QString tabName, bool enable);


private:
    Ui::alertwidget *ui;

    WidgetSettings Settings;
    GlobalSettings globalSettings;

    QTime alertTime;
    QTimer alertTick;
    QTimer blinkTimer;
    //QString alertName;

    bool blinking;
    bool blinky;

    QMediaPlaylist *playlist;
    QMediaPlayer *player;



    void mousePressEvent(QMouseEvent *e);


};


int getMsecs(const QTime& t);

int calculateDuration(const QTime& t);

#endif // ALERTWIDGET_H
