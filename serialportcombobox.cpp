/****************************************************************************
**
** Copyright (C) 2018 Miklos Marton <martonmiklosqdev@gmail.com>
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/
#include "serialportcombobox.h"

#include <QSerialPort>
#include <QSerialPortInfo>

SerialPortComboBox::SerialPortComboBox(QWidget *parent) :
    QComboBox(parent)
{
    refreshPorts();
}

/**
 * @brief SerialPortComboBox::refreshPorts
 * Refresh the combobox's items to match the available ports in the system.
 */
void SerialPortComboBox::refreshPorts()
{
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    /* Loop through the current combobox items and remove the non present ports */
    for (int i = 0; i<this->count(); i++) {
        bool portFound = false;
        foreach (const QSerialPortInfo &info, availablePorts) {
            if (info.portName() == this->itemText(i)) {
                portFound = true;
                break;
            }
        }

        if (!portFound) {
            this->removeItem(i);
            i--;
        }
    }

    /* Loop through the available ports and check that they are present in the combobox */
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        /* If a port is not present add it to the combobox */
        if (this->findText(info.portName()) == -1) {
#if defined(Q_OS_LINUX) || defined(Q_OS_MACOS)
            this->addItem(info.systemLocation(), info.systemLocation());
#else
            this->addItem(info.portName(), info.systemLocation());
#endif
            this->setItemData(this->count() - 1, info.description(), Description);
            this->setItemData(this->count() - 1, info.manufacturer(), Manufacturer);
            this->setItemData(this->count() - 1, info.serialNumber(), SerialNumber);
            this->setItemData(this->count() - 1, info.systemLocation(), Location);
            if (info.hasVendorIdentifier()) {
                this->setItemData(this->count() - 1,
                                  QString("0x%1").arg((uint)info.vendorIdentifier(), 4, 16, QChar('0')).toUpper(),
                                  VendorIdentifier);
            } else {
                this->setItemData(this->count() - 1, QStringLiteral(""), VendorIdentifier);
            }

            if (info.hasProductIdentifier()) {
                this->setItemData(this->count() - 1,
                                  QString("0x%1").arg((uint)info.productIdentifier(), 4, 16, QChar('0')).toUpper(),
                                  ProductIdentifier);
            } else {
                this->setItemData(this->count() - 1, QStringLiteral(""), ProductIdentifier);
            }
        }
    }
}

bool SerialPortComboBox::selectPort(const QString & portName)
{
    int itemIndex = this->findText(portName);
    if (itemIndex == -1)
        return false;
    this->setCurrentIndex(itemIndex);
    return true;
}

void SerialPortComboBox::showPopup()
{
    refreshPorts();
    QComboBox::showPopup();
}
