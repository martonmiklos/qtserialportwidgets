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
#include "baudratecombobox.h"

#include <QLineEdit>
#include <QMetaEnum>

BaudRateComboBox::BaudRateComboBox(QWidget *parent) :
    QComboBox(parent)
{
    fillBaudRates();
    setBaudRate(QSerialPort::Baud115200);
}


BaudRateComboBox::BaudRateComboBox(QSerialPort::BaudRate baudRate, QWidget *parent) :
    QComboBox(parent)
{
    fillBaudRates();
    setBaudRate(baudRate);
}

void BaudRateComboBox::fillBaudRates()
{
    QMetaEnum baudRateEnum = QMetaEnum::fromType<QSerialPort::BaudRate>();

    for (int i = 0; i<baudRateEnum.keyCount(); i++) {
        this->addItem(
                    QString(baudRateEnum.key(i)).mid(4),
                    baudRateEnum.value(i)
                );
    }
    this->addItem(tr("Custom"));
    intValidator = new QIntValidator(0, 4000000, this);

    this->setInsertPolicy(QComboBox::NoInsert);
    connect(this, SIGNAL(currentIndexChanged(int)),
            this, SLOT(checkCustomBaudRatePolicy(int)));
}

void BaudRateComboBox::setBaudRate(QSerialPort::BaudRate baudRate)
{
    int index = this->findData(baudRate);
    if (index != -1) {
        this->setCurrentIndex(index);
    } else  {
        index = this->count()-1;
        this->setCurrentIndex(index);
        this->setItemData(index, baudRate);
    }
}


QSerialPort::BaudRate BaudRateComboBox::baudRate()
{
    if (this->currentIndex() == this->count()-1) {
        // custom baud rate
        return static_cast<QSerialPort::BaudRate>(this->currentText().toInt());
    } else {
        // standard baud rate
        return static_cast<QSerialPort::BaudRate>(this->itemData(this->currentIndex()).toInt());
    }
}

void BaudRateComboBox::checkCustomBaudRatePolicy(int idx)
{
    bool isCustomBaudRate = !this->itemData(idx).isValid();
    this->setEditable(isCustomBaudRate);
    if (isCustomBaudRate) {
        this->clearEditText();
        QLineEdit *edit = this->lineEdit();
        edit->setValidator(intValidator);
    }
}
