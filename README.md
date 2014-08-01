

QtSerialWidgets
================================

This library contains the configuration widgets to be used in Qt widgets based applications using the QtSerialport library.

You can use it as a a library: compile the qtserialportwidgets.pro project and use the library files in the bin folder.
Or you can also include the qtserialportwidgets.pri file to your project and compile the widgets directly to your application.

If you are using Qt Designer for designing your user interface delegate your widget on the layout to the appropiate settings widget.
The pri file adds the QtSerialWidgets project's path to the INCLUDEPATHS so use global include for the delegation.

The library contains the following widgets:

SerialPortSettingsDialog:
A standard dialog for manipulating the serial port parameters. 
It also displays the retrived information about the current serial port.
This dialog is retrived from the QtSerialport Terminal example.
The dialog provides two methods for loading a QSerialPort settings to the gui and applying the gui settings to a QSerialPort instance. 
There is also an option for passing a QSerialPort pointer to the dialog to handle the configuration of the port by the GUI. 
In this case all configuration changes are taken into place after the pressing of the Apply button.

SerialPortComboBox:
A combobox which populates itself with the serial ports present on the system. The list is regenerated every time when the QComboBox's showPopup is called, so the plug'n play devices could be detected without any external coding. 

BaudRateComboBox:
A combobox showing the most common baudrates. It also have an option for specifying custom baud rates
