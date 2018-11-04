#ifndef CHANGEALARMDIALOG_H
#define CHANGEALARMDIALOG_H

#include "alertwidget.h"
#include "widgetsettings.h"

#include <QDialog>

namespace Ui {
class ChangeAlarmDialog;
}

class ChangeAlarmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeAlarmDialog(alertwidget *parent = nullptr);
    ~ChangeAlarmDialog();

public slots:
    void changeAlarm();
signals:
    void changeAlarmSignal(WidgetSettings settings);

private:
    Ui::ChangeAlarmDialog *ui;
};

#endif // CHANGEALARMDIALOG_H
