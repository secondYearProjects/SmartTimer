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

    void updateWidget(GlobalSettings _globalSettings);
public slots:
    void returnAndClose();
signals:
    void sendTimerData(WidgetSettings settings);


private:
    Ui::addTimerDialog *ui;
    GlobalSettings globalSettings;
};

#endif // ADDTIMERDIALOG_H
