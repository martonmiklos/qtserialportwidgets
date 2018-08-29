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
#include "paritycombobox.h"

ParityComboBox::ParityComboBox(QWidget *parent) :
    QComboBox(parent)
{
    fillParities();
    setParity(QSerialPort::NoParity);
}


ParityComboBox::ParityComboBox(QSerialPort::Parity parity, QWidget *parent) :
    QComboBox(parent)
{
    fillParities();
    setParity(parity);
}

void ParityComboBox::fillParities()
{
    this->addItem(QObject::tr("None"), QSerialPort::NoParity);
    this->addItem(QObject::tr("Even"), QSerialPort::EvenParity);
    this->addItem(QObject::tr("Odd"), QSerialPort::OddParity);
    this->addItem(QObject::tr("Mark"), QSerialPort::MarkParity);
    this->addItem(QObject::tr("Space"), QSerialPort::SpaceParity);
}

bool ParityComboBox::setParity(QSerialPort::Parity parity)
{
    int itemIndex = this->findData(parity);
    if (itemIndex == -1)
        return false;
    this->setCurrentIndex(itemIndex);
    return true;
}

QSerialPort::Parity ParityComboBox::parity()
{
    return static_cast<QSerialPort::Parity>(this->itemData(this->currentIndex()).toInt());
}

