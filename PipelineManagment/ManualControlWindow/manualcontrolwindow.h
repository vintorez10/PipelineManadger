#ifndef MANUALCONTROLWINDOW_H
#define MANUALCONTROLWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextBrowser>
#include <QPalette>
#include <QColor>
#include <QLocale>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDateTime>
#include <QString>

class ManualControlWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ManualControlWindow(QWidget *parent = nullptr);     

private:
    enum{FirstButton = 0, SecondButton = 1, ThirdButton = 2,
         FourthButton = 3, NumberButtons = 4};

    void createConntrolButtons();
    void setColorButton();   

    QPushButton* m_buttons[NumberButtons];
    QGroupBox* m_horisontalGroupBox;
    QVBoxLayout* m_mainLayout;
    QSerialPort* m_arduinoPort;
    QString m_event, m_dataTime;

public slots:
    void on_pushButtonFirstClicked();
    void on_pushButtonSecondClicked();
    void on_pushButtonThirdClicked();
    void on_pushButtonStopClicked();
    void showWindow();

signals:
    void callMainWindow();    
    void sendData(const QString& dataTime, const QString& message);
    void sendCommand(const char* command);

};

#endif // MANUALCONTROLWINDOW_H
