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
#ifndef DATABITSCOMBOBOX_H
#define DATABITSCOMBOBOX_H

#include <QComboBox>
#include <QtSerialPort/QSerialPort>

class DataBitsComboBox : public QComboBox
{
    Q_OBJECT
public:
    DataBitsComboBox(QWidget *parent = NULL);
    DataBitsComboBox(QSerialPort::DataBits dataBits = QSerialPort::Data8,
                     QWidget *parent = NULL);
    bool setDataBits(QSerialPort::DataBits dataBits);
    QSerialPort::DataBits dataBits();
private:
    void fillDataBits();
};

#endif // DATABITSCOMBOBOX_H
