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
#ifndef SERIALPORTCOMBOBOX_H
#define SERIALPORTCOMBOBOX_H

#include <QComboBox>
#include <QRegularExpression>
#include <QSerialPort>

class SerialPortComboBox : public QComboBox
{
    Q_OBJECT
public:
    enum SerialPortPropertyRole {
        Description = Qt::UserRole + 1,
        Manufacturer,
        Serialnumber,
        Location,
        VendorIdentifier,
        ProductIdentifier,
        PortName
    };
    Q_ENUM(SerialPortPropertyRole)


    enum DisplayMode {
        PortNameOnly,
        PortNameAndSerial,
        PortNameAndVIDPID,
        PortNameAndDescription
    };

    SerialPortComboBox(QWidget *parent = nullptr);
    SerialPortComboBox(DisplayMode displayMode, QWidget *parent = nullptr);
    bool selectPort(const QString &portName);
    void showPopup();

    void setProductIdentifierFilter(quint16 pidFilter, bool invertedFilter = false);
    void clearProductIdentifierFilter();

    void setVendorIdentifierFilter(quint16 vidFilter, bool invertedFilter = false);
    void clearVendorIdentifierFilter();

    /**
     * @brief setSerialFilter
     * Allow listing serial ports with a specific serial number.
     * @param serialFilter
     * Wildcarding with "?" and "*" is supported
     * @param invertedFilter
     * If true then the serial ports with serialnumber matching the serialFilter
     * will not be populated to the comboBox
     */
    void setSerialFilter(const QString & serialFilter, bool invertedFilter = false);


    QString currentPortName() const;
    void setCurrentPortName(const QString &portName);

    DisplayMode displayMode() const;
    void setDisplayMode(const DisplayMode &displayMode);

protected:
    void refreshPorts();

    quint16 m_pidFilter, m_vidFilter;
    bool m_pidFilterSet = false, m_vidFilterSet = false;
    bool m_pidFilterInverted = false, m_vidFilterInverted = false;
    DisplayMode m_displayMode = PortNameOnly;
    QString m_serialFilter;
    bool m_serialFilterSet = false;
    QRegularExpression m_serialFilterRe;
    bool m_serialFilterInverted = false;
};

#endif // SERIALPORTCOMBOBOX_H
