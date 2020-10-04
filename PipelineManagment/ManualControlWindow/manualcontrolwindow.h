#ifndef MANUALCONTROLWINDOW_H
#define MANUALCONTROLWINDOW_H

#include <pipelinemanager.h>

class PipelineManager;

class ManualControlWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ManualControlWindow(QWidget *parent = nullptr);

    void initArduiniPort();    

private:
    enum{FirstButton = 0, SecondButton = 1, ThirdButton = 2,
         FourthButton = 3, NumberButtons = 4};

    void createConntrolButtons();
    void setColorButton();   

    QPushButton* m_buttons[NumberButtons];
    QGroupBox* m_horisontalGroupBox;
    QVBoxLayout* m_mainLayout;
    QSerialPort* m_arduinoPort;
    QString m_arduinoPortName;
    PipelineManager* m_manager;

public slots:
    void on_pushButtonFirstClicked();
    void on_pushButtonSecondClicked();
    void on_pushButtonThirdClicked();
    void on_pushButtonStopClicked();


signals:
    void callMainWindow();
    void sendData(QString dataTime, QString message);

};

#endif // MANUALCONTROLWINDOW_H
