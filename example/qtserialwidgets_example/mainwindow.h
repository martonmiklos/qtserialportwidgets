#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "serialportsettingsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_toolButtonSettings_clicked();

private:
    Ui::MainWindow *ui;
    SerialPortSettingsDialog *m_settingsDialog;
};

#endif // MAINWINDOW_H
