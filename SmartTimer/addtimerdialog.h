#ifndef ADDTIMERDIALOG_H
#define ADDTIMERDIALOG_H

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
    int sendTime(int msecs);


private:
    Ui::addTimerDialog *ui;
};

#endif // ADDTIMERDIALOG_H
