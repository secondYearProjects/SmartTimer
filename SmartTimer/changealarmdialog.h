#ifndef CHANGEALARMDIALOG_H
#define CHANGEALARMDIALOG_H

#include "alertwidget.h"

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
    void changeAlarmSignal(int, const QString &);

private:
    Ui::ChangeAlarmDialog *ui;
};

#endif // CHANGEALARMDIALOG_H
