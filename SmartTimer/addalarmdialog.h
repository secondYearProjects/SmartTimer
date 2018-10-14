#ifndef ADDALARMDIALOG_H
#define ADDALARMDIALOG_H

#include <QDialog>

namespace Ui {
class addAlarmDialog;
}

class addAlarmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addAlarmDialog(QWidget *parent = nullptr);
    ~addAlarmDialog();
public slots:
    void sendData();
signals:
    void sendAlarmData(int,const QString&);
private:
    Ui::addAlarmDialog *ui;
};

#endif // ADDALARMDIALOG_H
