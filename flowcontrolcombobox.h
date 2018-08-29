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
#ifndef FLOWCONTROLCOMBOBOX_H
#define FLOWCONTROLCOMBOBOX_H

#include <QComboBox>
#include <QSerialPort>

class FlowControlComboBox : public QComboBox
{
    Q_OBJECT
public:
    FlowControlComboBox(QWidget *parent = NULL);
    FlowControlComboBox(QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl,
                        QWidget *parent = NULL);
    bool setFlowControl(QSerialPort::FlowControl flowControl);
    QSerialPort::FlowControl flowControl();
private:
    void fillFlowControls();
};

#endif // FLOWCONTROLCOMBOBOX_H
