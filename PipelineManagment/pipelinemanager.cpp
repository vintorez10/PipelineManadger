#include "pipelinemanager.h"


PipelineManager::PipelineManager(QWidget *parent)
    : QWidget(parent)
{
    m_logTable = new QTableWidget;
    m_arduinoPort = new QSerialPort;
    m_logErrorWindow = new QTextBrowser;    

    createConntrolButtons();
    createPipelineStatusTable();

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(m_horizantalButtonBox);
    m_mainLayout->addWidget(m_horizontalLogBox, Qt::AlignTop);
    setLayout(m_mainLayout);

    connect(m_buttons[FirstButton], &QPushButton::clicked,
            this, &PipelineManager::on_pushButtonStartClicked);

    connect(m_buttons[SecondButton], &QPushButton::clicked,
            this, &PipelineManager::on_pushButtonStopClicked);

    connect(m_buttons[ThirdButton], &QPushButton::clicked,
            this, &PipelineManager::on_pushButtonManualControlClicked);

//    connect(m_windowControl, &ManualControlWindow::sendData,
//            this, &PipelineManager::sendDataToPipeline);


}

PipelineManager::~PipelineManager()
{
    if(m_arduinoPort->isOpen()){

        //Close the serial port
        m_arduinoPort->close();
    }
}

void PipelineManager::createConntrolButtons()
{
    QHBoxLayout* layout = new QHBoxLayout;

    m_horizantalButtonBox = new QGroupBox("Control buttons");

    m_buttons[FirstButton] = new QPushButton("START");
    m_buttons[SecondButton] = new QPushButton("STOP");
    m_buttons[ThirdButton] = new QPushButton("MANUAL CONTROL");

    //setting the color for button
    QPalette palStart = m_buttons[FirstButton]->palette();
    palStart.setColor(QPalette::Button, QColor(Qt::green));
    m_buttons[FirstButton]->setAutoFillBackground(true);
    m_buttons[FirstButton]->setPalette(palStart);
    m_buttons[FirstButton]->update();

    QPalette palStop = m_buttons[SecondButton]->palette();
    palStop.setColor(QPalette::Button, QColor(Qt::red));
    m_buttons[SecondButton]->setAutoFillBackground(true);
    m_buttons[SecondButton]->setPalette(palStop);
    m_buttons[SecondButton]->update();

    //m_buttons[0]->setStyleSheet("background-color: green;");

    for(auto& a: m_buttons){
        layout->addWidget(a);
    }

    m_horizantalButtonBox->setLayout(layout);

}

void PipelineManager::createPipelineStatusTable()
{
    QHBoxLayout* layout = new QHBoxLayout;

    m_horizontalLogBox = new QGroupBox("Informathion about pipline operation");

    m_logErrorWindow->setText("Here, you will see messages about the state"
                              "of the system and its malfunctions");

    layout->addWidget(m_logTable, 0, Qt::AlignLeft);
    layout->addWidget(m_logErrorWindow);

    m_horizontalLogBox->setLayout(layout);

}

void PipelineManager::on_pushButtonStartClicked()
{
    //sending the button state
    setState(true);

    //initializing the port
    initArduinoPort();

    //when we click button we making this button invisible
    m_buttons[ThirdButton]->setEnabled(false);

    //commands to start all pipelines
    char startCommands[3] = {'a', 'b', 'c'};

    //start all pipelines
    sendStartToPipeline(startCommands);

    //message for the event
    QString event{"Start all pipelines"};

    //time and date for the event
    QString dataTime = getDataTime();    

    addDataTable(dataTime, event);

}

void PipelineManager::on_pushButtonStopClicked()
{
    //sending the button state
    setState(false);

    //when we click button we making this button is visible
    m_buttons[ThirdButton]->setEnabled(true);

    char stopCommands[3] = {'x', 'y', 'z'};

    sendStopToPipeline(stopCommands);

    QString event{"Stop all pipelines"};
    QString dataTime = getDataTime();

    addDataTable(dataTime, event);


}

void PipelineManager::on_pushButtonManualControlClicked()
{
    //initilalizing the manual control window
    ManualControlWindow*  m_windowControl = new ManualControlWindow;

    //call manual control window
    m_windowControl->setFixedSize(800, 400);
    m_windowControl->show();


}

void PipelineManager::initArduinoPort()
{
    //getting a list of all available ports
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){

        m_arduinoPortName = serialPortInfo.portName();

    }

    m_arduinoPort->setPortName(m_arduinoPortName);
    m_arduinoPort->setBaudRate(QSerialPort::Baud9600);
    m_arduinoPort->setDataBits(QSerialPort::Data8);
    m_arduinoPort->setParity(QSerialPort::NoParity);
    m_arduinoPort->setStopBits(QSerialPort::OneStop);
    m_arduinoPort->setFlowControl(QSerialPort::NoFlowControl);

    if(m_arduinoPort->open(QIODevice::ReadWrite)){
        qDebug() << "Pipline connected";
    }
    else{
        qDebug() << "Pipline no connected!";
    }

}

void PipelineManager::setState(bool state)
{
    //according to the received value, we make the buttons
    //non-clicable
    if(state){
        m_buttons[FirstButton]->setEnabled(false);
        m_buttons[SecondButton]->setEnabled(true);
    }
    else{
        m_buttons[FirstButton]->setEnabled(true);
        m_buttons[SecondButton]->setEnabled(false);
    }

}

void PipelineManager::sendStartToPipeline(const char* dataStart)
{
    m_arduinoPort->write(dataStart, sizeof (dataStart));
    m_arduinoPort->waitForBytesWritten();

    for (int i{0}; i != 3; ++i) {
        qDebug() << dataStart[i];
    }

}

void PipelineManager::sendStopToPipeline(const char* dataStop)
{
    m_arduinoPort->write(dataStop, sizeof (dataStop));
    m_arduinoPort->waitForBytesWritten();

    for (int i{0}; i != 3; ++i) {
        qDebug() << dataStop[i];
    }

}

void PipelineManager::addDataTable(const QString& dataTime, const QString& message)
{
    QStringList headers;
    m_logTable->setColumnCount(2);
    headers << "Time" << "Event";
    m_logTable->setHorizontalHeaderLabels(headers);

    //filling in the table with events
    if(m_logTable->rowCount() <= m_count){
        m_logTable->setRowCount(m_count + 1);
        m_logTable->setItem(m_count, 0, new QTableWidgetItem(dataTime));
        m_logTable->setItem(m_count, 1, new QTableWidgetItem(message));
        m_count++;
    }

}
