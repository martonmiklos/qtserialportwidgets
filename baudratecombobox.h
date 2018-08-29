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
#ifndef BAUDRATECOMBOBOX_H
#define BAUDRATECOMBOBOX_H


#include <QComboBox>
#include <QSerialPort>

class BaudRateComboBox : public QComboBox
{
    Q_OBJECT
public:
    BaudRateComboBox(QWidget *parent = NULL);
    BaudRateComboBox(QSerialPort::BaudRate baudRate = QSerialPort::Baud115200,
                     QWidget *parent = NULL);
    void setBaudRate(QSerialPort::BaudRate baudRate);
    QSerialPort::BaudRate baudRate();
private:
    QIntValidator *intValidator;
    void fillBaudRates();

private slots:
    void checkCustomBaudRatePolicy(int idx);
};

#endif // BAUDRATECOMBOBOX_H
