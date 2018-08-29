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
#include "databitscombobox.h"

#include <QtSerialPort/QSerialPort>

DataBitsComboBox::DataBitsComboBox(QWidget *parent) :
    QComboBox(parent)
{
    fillDataBits();
    this->setDataBits(QSerialPort::Data8);
}

DataBitsComboBox::DataBitsComboBox(QSerialPort::DataBits dataBits, QWidget *parent) :
    QComboBox(parent)
{
    fillDataBits();
    this->setDataBits(dataBits);
}

void DataBitsComboBox::fillDataBits()
{
    this->addItem(QStringLiteral("5"), QSerialPort::Data5);
    this->addItem(QStringLiteral("6"), QSerialPort::Data6);
    this->addItem(QStringLiteral("7"), QSerialPort::Data7);
    this->addItem(QStringLiteral("8"), QSerialPort::Data8);
}

bool DataBitsComboBox::setDataBits(QSerialPort::DataBits dataBits)
{
    int itemIndex = this->findData(dataBits);
    if (itemIndex == -1)
        return false;
    this->setCurrentIndex(itemIndex);
    return true;
}

QSerialPort::DataBits DataBitsComboBox::dataBits()
{
    return static_cast<QSerialPort::DataBits>(this->itemData(this->currentIndex()).toInt());
}
