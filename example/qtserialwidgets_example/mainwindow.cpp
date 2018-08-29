#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_settingsDialog = new SerialPortSettingsDialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButtonSettings_clicked()
{
    m_settingsDialog->show();
}
