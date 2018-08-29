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
#include "stopbitscombobox.h"

StopBitsComboBox::StopBitsComboBox(QWidget *parent) :
    QComboBox(parent)
{
    fillStopBits();
    setStopBits(QSerialPort::OneStop);
}

StopBitsComboBox::StopBitsComboBox(QSerialPort::StopBits stopBits, QWidget *parent) :
    QComboBox(parent)
{
    fillStopBits();
    setStopBits(stopBits);
}

void StopBitsComboBox::fillStopBits()
{
    this->addItem(QStringLiteral("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    this->addItem(QStringLiteral("1.5"), QSerialPort::OneAndHalfStop);
#endif
    this->addItem(QStringLiteral("2"), QSerialPort::TwoStop);
}

bool StopBitsComboBox::setStopBits(QSerialPort::StopBits stopBits)
{
    int itemIndex = this->findData(stopBits);
    if (itemIndex == -1)
        return false;
    this->setCurrentIndex(itemIndex);
    return true;
}

QSerialPort::StopBits StopBitsComboBox::stopBits()
{
    return static_cast<QSerialPort::StopBits>(this->itemData(this->currentIndex()).toInt());
}

