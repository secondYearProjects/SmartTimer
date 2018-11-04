#ifndef CHANGETIMERDIALOG_H
#define CHANGETIMERDIALOG_H

#include "timerwidget.h"
#include "widgetsettings.h"

#include <QDialog>

namespace Ui {
class ChangeTimerDialog;
}

class ChangeTimerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeTimerDialog(TimerWidget *parent = nullptr);
    ~ChangeTimerDialog();

public slots:
    void changeTimerAndQuit();

private:
    Ui::ChangeTimerDialog *ui;
    TimerWidget *par;
};

#endif // CHANGETIMERDIALOG_H
