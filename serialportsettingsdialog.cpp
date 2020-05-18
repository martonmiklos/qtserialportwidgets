/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
** Copyright (C) 2014 Miklos Marton <martonmiklosqdev@gmail.com>
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "serialportsettingsdialog.h"
#include "ui_serialportsettingsdialog.h"

#include <QSerialPortInfo>
#include <QLineEdit>

QT_USE_NAMESPACE

SerialPortSettingsDialog::SerialPortSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialPortSettingsDialog),
    widgetCount(0),
    m_port(nullptr)
{
    ui->setupUi(this);
    ui->baudRateBox->setBaudRate(QSerialPort::Baud9600);
    on_serialPortInfoListBox_activated(ui->serialPortInfoListBox->currentIndex());
    updateSettings();
}

SerialPortSettingsDialog::~SerialPortSettingsDialog()
{
    delete ui;
}

void SerialPortSettingsDialog::addWidget(QWidget *widget)
{
    ui->gridLayout_3->addWidget(widget, widgetCount+1, 0, 1, 2);
    widgetCount++;
}

void SerialPortSettingsDialog::loadSettingsFromPort(QSerialPort *port)
{
    int index = ui->serialPortInfoListBox->findText(port->portName());
    if (index != -1) {
        ui->serialPortInfoListBox->setCurrentIndex(index);
        ui->baudRateBox->setBaudRate(static_cast<QSerialPort::BaudRate>(port->baudRate()));
        ui->dataBitsBox->setDataBits(port->dataBits());
        ui->parityBox->setParity(port->parity());
        ui->stopBitsBox->setStopBits(port->stopBits());
        ui->flowControlBox->setFlowControl(port->flowControl());
        on_serialPortInfoListBox_activated(ui->serialPortInfoListBox->currentIndex());
        updateSettings();
    }
}

void SerialPortSettingsDialog::applySettingsToPort(QSerialPort *port)
{
    port->setPortName(ui->serialPortInfoListBox->itemData(ui->serialPortInfoListBox->currentIndex()).toString());
    port->setBaudRate(ui->baudRateBox->baudRate());
    port->setDataBits(ui->dataBitsBox->dataBits());
    port->setParity(ui->parityBox->parity());
    port->setStopBits(ui->stopBitsBox->stopBits());
    port->setFlowControl(ui->flowControlBox->flowControl());
}

void SerialPortSettingsDialog::loadSettings(QSettings &settings)
{
    QString portName = settings.value("portName", "").toString();
    int index = ui->serialPortInfoListBox->findText(portName);
    if (index != -1)
        ui->serialPortInfoListBox->setCurrentIndex(index);
    ui->baudRateBox->setBaudRate(static_cast<QSerialPort::BaudRate>(settings.value("baudRate", QSerialPort::Baud115200).toInt()));
    ui->dataBitsBox->setDataBits(static_cast<QSerialPort::DataBits>(settings.value("dataBits", QSerialPort::Data8).toInt()));
    ui->parityBox->setParity(static_cast<QSerialPort::Parity>(settings.value("parity", QSerialPort::NoParity).toInt()));
    ui->stopBitsBox->setStopBits(static_cast<QSerialPort::StopBits>(settings.value("stopBits", QSerialPort::OneStop).toInt()));
    ui->flowControlBox->setFlowControl(static_cast<QSerialPort::FlowControl>(settings.value("baudRate", QSerialPort::NoFlowControl).toInt()));
}

void SerialPortSettingsDialog::saveSettings(QSettings &settings)
{
    settings.setValue("portName", ui->serialPortInfoListBox->itemData(ui->serialPortInfoListBox->currentIndex()).toStringList().first());
    settings.setValue("baudRate", ui->baudRateBox->baudRate());
    settings.setValue("dataBits", ui->dataBitsBox->dataBits());
    settings.setValue("parity", ui->parityBox->parity());
    settings.setValue("stopBits", ui->stopBitsBox->stopBits());
    settings.setValue("flowControl", ui->flowControlBox->flowControl());
}

void SerialPortSettingsDialog::setPort(QSerialPort *port)
{
    m_port = port;
}

SerialPortSettingsDialog::Settings SerialPortSettingsDialog::settings() const
{
    return currentSettings;
}

void SerialPortSettingsDialog::updateSettings()
{
    currentSettings.name = ui->serialPortInfoListBox->itemData(ui->serialPortInfoListBox->currentIndex()).toStringList().first();

    currentSettings.baudRate = ui->baudRateBox->baudRate();
    currentSettings.stringBaudRate = QString::number(currentSettings.baudRate);

    // Data bits
    currentSettings.dataBits = ui->dataBitsBox->dataBits();
    currentSettings.stringDataBits = ui->dataBitsBox->currentText();

    // Parity
    currentSettings.parity = ui->parityBox->parity();
    currentSettings.stringParity = ui->parityBox->currentText();

    // Stop bits
    currentSettings.stopBits = ui->stopBitsBox->stopBits();
    currentSettings.stringStopBits = ui->stopBitsBox->currentText();

    // Flow control
    currentSettings.flowControl = ui->flowControlBox->flowControl();
    currentSettings.stringFlowControl = ui->flowControlBox->currentText();
}

void SerialPortSettingsDialog::applyPortSettings(QSerialPort *port)
{
    port->setPortName(ui->serialPortInfoListBox->itemData(ui->serialPortInfoListBox->currentIndex()).toString());
    port->setBaudRate(ui->baudRateBox->baudRate());
    port->setDataBits(ui->dataBitsBox->dataBits());
    port->setParity(ui->parityBox->parity());
    port->setStopBits(ui->stopBitsBox->stopBits());
    port->setFlowControl(ui->flowControlBox->flowControl());
}

void SerialPortSettingsDialog::on_applyButton_clicked()
{
    updateSettings();
    hide();

    if (m_port != nullptr) {
        // a port is available to handle
        if (m_port->portName() != ui->serialPortInfoListBox->currentText()) {
            // using a different port now
            if (m_port->isOpen()) {
                // close the previously selected port
                m_port->close();

                m_port->setPortName(ui->serialPortInfoListBox->currentText());
                applySettingsToPort(m_port);
                m_port->open(QSerialPort::ReadWrite);
            }
        } else {
            // using the same port apply the settings and good to go
            applySettingsToPort(m_port);
        }
        emit portSettingsApplied();
    }
}

void SerialPortSettingsDialog::on_serialPortInfoListBox_activated(int index)
{
    if (index != -1) {
        ui->descriptionLabel->setText(
                    tr("Description: %1")
                    .arg(ui->serialPortInfoListBox->itemData(index, SerialPortComboBox::Description).toString()));
        ui->manufacturerLabel->setText(
                    tr("Manufacturer: %1")
                    .arg(ui->serialPortInfoListBox->itemData(index, SerialPortComboBox::Description).toString()));
        ui->serialNumberLabel->setText(
                    tr("Serial number: %1")
                    .arg(ui->serialPortInfoListBox->itemData(index, SerialPortComboBox::Serialnumber).toString()));
        ui->locationLabel->setText(
                    tr("Location: %1")
                    .arg(ui->serialPortInfoListBox->itemData(index, SerialPortComboBox::Location).toString()));
        ui->vidLabel->setText(
                    tr("Vendor Identifier: %1")
                    .arg(ui->serialPortInfoListBox->itemData(index, SerialPortComboBox::VendorIdentifier).toString()));
        ui->pidLabel->setText(
                    tr("Product Identifier: %1")
                    .arg(ui->serialPortInfoListBox->itemData(index, SerialPortComboBox::ProductIdentifier).toString()));
    }
}
