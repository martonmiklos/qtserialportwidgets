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
#include "flowcontrolcombobox.h"

FlowControlComboBox::FlowControlComboBox(QWidget *parent) :
    QComboBox(parent)
{
    fillFlowControls();
    setFlowControl(QSerialPort::NoFlowControl);
}

FlowControlComboBox::FlowControlComboBox(QSerialPort::FlowControl flowControl, QWidget *parent) :
    QComboBox(parent)
{
    fillFlowControls();
    setFlowControl(flowControl);
}

void FlowControlComboBox::fillFlowControls()
{
    this->addItem(QObject::tr("None"), QSerialPort::NoFlowControl);
    this->addItem(QStringLiteral("RTS/CTS"), QSerialPort::HardwareControl);
    this->addItem(QStringLiteral("XON/XOFF"), QSerialPort::SoftwareControl);
}

bool FlowControlComboBox::setFlowControl(QSerialPort::FlowControl flowControl)
{
    int itemIndex = this->findData(flowControl);
    if (itemIndex == -1)
        return false;
    this->setCurrentIndex(itemIndex);
    return true;
}

QSerialPort::FlowControl FlowControlComboBox::flowControl()
{
    return static_cast<QSerialPort::FlowControl>(this->itemData(this->currentIndex()).toInt());
}
