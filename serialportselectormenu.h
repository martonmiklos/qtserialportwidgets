#ifndef SERIALPORTSELECTORMENU_H
#define SERIALPORTSELECTORMENU_H


#include <QMenu>
#include <QSerialPort>
#include "qtserialportwidgets_global.h"

class QTSERIALPORTWIDGETS_EXPORT SerialportSelectorMenu
{
public:
    SerialportSelectorMenu();
    SerialportSelectorMenu(QMenu *menu, QSerialPort *port);

    void fillMenu(QMenu *menu, QSerialPort *port);

private:
    QMenu *m_menu;
    QSerialPort *m_serialPort;
};

#endif // SERIALPORTSELECTORMENU_H
