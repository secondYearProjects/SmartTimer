#ifndef ADDTIMERDIALOG_H
#define ADDTIMERDIALOG_H

#include "widgetsettings.h"

#include <QDialog>

namespace Ui {
class addTimerDialog;
}

class addTimerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addTimerDialog(QWidget *parent = nullptr);
    ~addTimerDialog();

public slots:
    void returnAndClose();
signals:
    void sendTimerData(WidgetSettings settings);


private:
    Ui::addTimerDialog *ui;
};

#endif // ADDTIMERDIALOG_H
