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

SerialPortComboBox::SerialPortComboBox(SerialPortComboBox::DisplayMode displayMode, QWidget *parent) :
    QComboBox(parent),
    m_displayMode(displayMode)
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
    for (int i = 0; i<count(); i++) {
        bool leaveExistingPort = false;
        foreach (const QSerialPortInfo &info, availablePorts) {
            if (info.portName() == itemData(i).toString()) {
                leaveExistingPort = true;
                if (
                        (!m_vidFilterInverted && m_vidFilterSet && info.vendorIdentifier() != m_vidFilter) ||
                        (!m_pidFilterInverted && m_pidFilterSet && info.productIdentifier() != m_pidFilter) ||
                        (m_vidFilterInverted && m_vidFilterSet && info.vendorIdentifier() == m_vidFilter) ||
                        (m_pidFilterInverted && m_pidFilterSet && info.productIdentifier() == m_pidFilter)
                        ) {
                    // an existing port filtered out by the PID/VID filter -> remove it
                    leaveExistingPort = false;
                }
                break;
            }
        }

        if (!leaveExistingPort) {
            removeItem(i);
            i--;
        }
    }

    /* Loop through the available ports and check that they are present in the combobox */
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        /* If a port is not present add it to the combobox */
        if (findText(info.portName()) == -1) {
            if ((m_vidFilterSet &&
                 (((!m_vidFilterInverted && (info.vendorIdentifier() != m_vidFilter)) || (m_vidFilterInverted && (info.vendorIdentifier() == m_vidFilter))))) ||
                    (m_pidFilterSet &&
                     ((!m_pidFilterInverted && (info.productIdentifier() != m_pidFilter)) || (m_pidFilterInverted && (info.productIdentifier() == m_pidFilter))))
                    ) {
                // skip this port if it filtered out
                continue;
            }

            if (m_serialFilterSet) {
                auto matches = m_serialFilterRe.match(info.serialNumber());
                if (m_serialFilterInverted) {
                    if (matches.hasMatch())
                        continue;
                } else {
                    if (!matches.hasMatch())
                        continue;
                }
            }

            QString displayedText, portName;
#if defined(Q_OS_LINUX) || defined(Q_OS_MACOS)
            displayedText = info.systemLocation();
#else
            displayedText = info.portName();
#endif
            portName = displayedText;
            switch (m_displayMode) {
            case PortNameOnly:
                break;
            case PortNameAndSerial:
                if (info.serialNumber().isEmpty())
                    displayedText.append(tr(" (SN Unsupported)"));
                else
                    displayedText.append(QStringLiteral(" (%1)").arg(info.serialNumber()));
                break;
            case PortNameAndVIDPID:
                if (info.vendorIdentifier() == 0 && info.productIdentifier() == 0)
                    displayedText.append(tr(" (no VID,PID)"));
                else
                    displayedText.append(QString(" (%1:%2)")
                                         .arg(info.vendorIdentifier(), 4, 16, QChar('0'))
                                         .arg(info.productIdentifier(), 4, 16, QChar('0')));
                break;
            case PortNameAndDescription:
                if (info.description().isEmpty())
                    displayedText.append(tr(" (no description)"));
                else
                    displayedText.append(QStringLiteral(" (%1)").arg(info.description()));
                break;
            }
            addItem(displayedText, info.systemLocation());

            setItemData(count() - 1, portName, PortName);
            setItemData(count() - 1, info.description(), Description);
            setItemData(count() - 1, info.manufacturer(), Manufacturer);
            setItemData(count() - 1, info.serialNumber(), Serialnumber);
            setItemData(count() - 1, info.systemLocation(), Location);
            if (info.hasVendorIdentifier()) {
                setItemData(count() - 1,
                            QString("0x%1").arg((uint)info.vendorIdentifier(), 4, 16, QChar('0')).toUpper(),
                            VendorIdentifier);
            } else {
                setItemData(count() - 1, QString(), VendorIdentifier);
            }

            if (info.hasProductIdentifier()) {
                setItemData(count() - 1,
                            QString("0x%1").arg((uint)info.productIdentifier(), 4, 16, QChar('0')).toUpper(),
                            ProductIdentifier);
            } else {
                setItemData(count() - 1, QString(), ProductIdentifier);
            }
        }
    }
}

SerialPortComboBox::DisplayMode SerialPortComboBox::displayMode() const
{
    return m_displayMode;
}

void SerialPortComboBox::setDisplayMode(const DisplayMode &displayMode)
{
    m_displayMode = displayMode;
}

bool SerialPortComboBox::selectPort(const QString & portName)
{
    int itemIndex = findText(portName);
    if (itemIndex == -1)
        return false;
    setCurrentIndex(itemIndex);
    return true;
}

void SerialPortComboBox::showPopup()
{
    refreshPorts();
    QComboBox::showPopup();
}

void SerialPortComboBox::setProductIdentifierFilter(quint16 pidFilter, bool invertedFilter)
{
    m_pidFilter = pidFilter;
    m_pidFilterSet = true;
    m_pidFilterInverted = invertedFilter;
    refreshPorts();
}

void SerialPortComboBox::setVendorIdentifierFilter(quint16 vidFilter, bool invertedFilter)
{
    m_vidFilter = vidFilter;
    m_vidFilterSet = true;
    m_vidFilterInverted = invertedFilter;
    refreshPorts();
}

void SerialPortComboBox::setSerialFilter(const QString &serialFilter, bool invertedFilter)
{
    m_serialFilterSet = !serialFilter.isEmpty();
    if (m_serialFilterSet) {
        m_serialFilterInverted = invertedFilter;
        auto pattern = serialFilter;
        pattern.replace("*", ".*");
        pattern.replace("?", ".{1}");
        m_serialFilterRe.setPattern(pattern);
    }
}

void SerialPortComboBox::clearProductIdentifierFilter()
{
    m_pidFilterSet = false;
    refreshPorts();
}

void SerialPortComboBox::clearVendorIdentifierFilter()
{
    m_vidFilterSet = false;
    refreshPorts();
}

QString SerialPortComboBox::currentPortName() const
{
    return itemData(currentIndex(), SerialPortComboBox::PortName).toString();
}

void SerialPortComboBox::setCurrentPortName(const QString &portName)
{
    setCurrentIndex(findData(portName, SerialPortComboBox::PortName));
}
