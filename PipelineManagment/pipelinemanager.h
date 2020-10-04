#ifndef PIPELINEMANAGER_H
#define PIPELINEMANAGER_H

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
#include <manualcontrolwindow.h>


class PipelineManager : public QWidget
{
    Q_OBJECT

public:
    PipelineManager(QWidget *parent = nullptr);
    ~PipelineManager();

    void initArduinoPort();
    void addDataTable(const QString& dataTime, const QString& message);
    void sendStartToPipeline(const char* dataStart);
    void sendStopToPipeline(const char* dataStop);
    QString getDataTime(){return  QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");}
    int m_count;    

private slots:
    void on_pushButtonStartClicked();
    void on_pushButtonStopClicked();
    void on_pushButtonManualControlClicked();

private:
    enum{FirstButton = 0, SecondButton = 1,
         ThirdButton = 2, NumberButtons = 3};

    void createConntrolButtons();
    void createPipelineStatusTable();
    void setState(bool state);    

    QVBoxLayout* m_mainLayout;
    QGroupBox* m_horizantalButtonBox;
    QGroupBox* m_horizontalLogBox;
    QPushButton* m_buttons[NumberButtons];
    QTableWidget* m_logTable;
    QTableWidgetItem* m_logItem;
    QTextBrowser* m_logErrorWindow;
    QSerialPort* m_arduinoPort;   
    QString m_arduinoPortName;   

};
#endif // PIPELINEMANAGER_H
