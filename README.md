

QtSerialWidgets
================================

This library contains the configuration widgets to be used in Qt widgets based applications using the QtSerialport library.

You can use it as a a library: compile the qtserialportwidgets.pro project and use the library files in the bin folder.
Or you can also include the qtserialportwidgets.pri file to your project and compile the widgets directly to your application.

If you are using Qt Designer for designing your user interface delegate your widget on the layout to the appropiate settings widget.
The pri file adds the QtSerialWidgets project's path to the INCLUDEPATHS so use global include for the delegation.

The library contains the following widgets:

## SerialPortSettingsDialog:

![SerialPortSettingsDialog](https://raw.githubusercontent.com/martonmiklos/qtserialportwidgets/master/images/serialportsettingsdialog.png "SerialPortSettingsDialog in action")

 * A standard dialog for manipulating the serial port parameters. 
 * It also displays the retrived information about the current serial port.
 * This dialog is based on the [QtSerialport Terminal example](https://github.com/qt/qtserialport/tree/5.11/examples/serialport/terminal).
 * The dialog provides two methods for loading a QSerialPort settings to the gui and applying the gui settings to a QSerialPort instance (loadSettingsFromPort and applySettingsToPort). 
 * There is also an option for passing a QSerialPort pointer to the dialog to handle the configuration of the port by the GUI. 
 * In this case all configuration changes are taken into place after the pressing of the Apply button.
 * The settings of the dialog can be saved and restored through a configured QSetting object with the saveSettings(QSettings &) and loadSettings(QSettings &) methods.

## SerialPortComboBox:

![SerialPortSettingsDialog](https://raw.githubusercontent.com/martonmiklos/qtserialportwidgets/master/images/serialportcombobox.png "SerialPortSettingsDialog in action")

 * A  combobox which populates itself with the serial ports present on the system. The list is regenerated every time when the QComboBox's showPopup is called, so the plug'n play devices could be detected without any external coding. 
 * The port informations (provided by the QSerialPortInfo) like [serial number](http://doc.qt.io/qt-5/qserialportinfo.html#serialNumber), [manufacturer](http://doc.qt.io/qt-5/qserialportinfo.html#manufacturer), etc. can be accessed from the [itemData](http://doc.qt.io/qt-5/qcombobox.html#itemData) method with the roles above [Qt::UserRole](http://doc.qt.io/qt-5/qt.html#ItemDataRole-enum)

## BaudRateComboBox:

![BaudRateComboBox](https://raw.githubusercontent.com/martonmiklos/qtserialportwidgets/master/images/baudratecombobox.png "BaudRateComboBox in action")

 * A combobox showing the [baudrates supported by the system](http://doc.qt.io/qt-5/qserialportinfo.html#standardBaudRates)

## DataBitsComboBox:
 * A combobox for specifying the number of data bits.

## ParityComboBox:
 * A combobox for specifying the parity.

## StopbBitsComboBox:
 * A combobox for specifying the number of stop bits.
