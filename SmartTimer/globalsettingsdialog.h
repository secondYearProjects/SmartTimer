#ifndef GLOBALSETTINGSDIALOG_H
#define GLOBALSETTINGSDIALOG_H

#include "widgetsettings.h"

#include <QDialog>

namespace Ui {
class GlobalSettingsDialog;
}

class GlobalSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GlobalSettingsDialog(GlobalSettings old, QWidget *parent = nullptr);
    ~GlobalSettingsDialog();
public slots:
    void confirmed();
    void canceled();
    void opacityChanged();
    void rangeChanged(int min,int max);
    void DDenableState(bool state);
signals:
    void changeSettings(GlobalSettings settings);

private:
    Ui::GlobalSettingsDialog *ui;

    GlobalSettings oldSettings;
};

#endif // GLOBALSETTINGSDIALOG_H
