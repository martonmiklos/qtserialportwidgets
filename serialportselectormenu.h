#ifndef SERIALPORTSELECTORMENU_H
#define SERIALPORTSELECTORMENU_H


#include <QMenu>
#include <QSerialPort>

class SerialportSelectorMenu
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
