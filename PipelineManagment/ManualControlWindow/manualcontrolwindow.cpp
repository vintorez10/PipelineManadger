#include "manualcontrolwindow.h"


ManualControlWindow::ManualControlWindow(QWidget *parent) : QWidget(parent)
{   
    createConntrolButtons();

    m_manager = new PipelineManager;

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(m_horisontalGroupBox);
    setLayout(m_mainLayout);

    connect(this, &ManualControlWindow::sendData,
            m_manager, &PipelineManager::addDataTable);

    connect(m_buttons[FirstButton], &QPushButton::clicked,
            this, &ManualControlWindow::on_pushButtonFirstClicked);

    connect(m_buttons[SecondButton], &QPushButton::clicked,
            this, &ManualControlWindow::on_pushButtonSecondClicked);

    connect(m_buttons[ThirdButton], &QPushButton::clicked,
            this, &ManualControlWindow::on_pushButtonThirdClicked);

    connect(m_buttons[FourthButton], &QPushButton::clicked,
            this, &ManualControlWindow::on_pushButtonStopClicked);

}

void ManualControlWindow::createConntrolButtons()
{
    QHBoxLayout* layout = new QHBoxLayout;
    m_horisontalGroupBox = new QGroupBox("Control buttons");

    m_buttons[FirstButton] = new QPushButton("Start First pipeline");
    m_buttons[SecondButton] = new QPushButton("Start Second pipeline");
    m_buttons[ThirdButton] = new QPushButton("Start Third pipeline");
    m_buttons[FourthButton] = new QPushButton("STOP all pipeline");

    //adding the color for the buttons
    setColorButton();

    for(auto& a: m_buttons){
        layout->addWidget(a);
    }

    layout->setAlignment(Qt::AlignmentFlag::AlignTop);

    m_horisontalGroupBox->setLayout(layout);

}

void ManualControlWindow::on_pushButtonFirstClicked()
{
    //when we click button we making this button invisible
    m_buttons[FirstButton]->setEnabled(false);

    //and "StopClicked" button we making visible
    m_buttons[FourthButton]->setEnabled(true);

    char firstPipe[] = {'a'};

    m_manager->sendStartToPipeline(firstPipe);

    QString event{"Start first pipeline"};
    QString dataTime = m_manager->getDataTime();

    emit sendData(event, dataTime);

}

void ManualControlWindow::on_pushButtonSecondClicked()
{
    //when we click button we making this button invisible
    m_buttons[SecondButton]->setEnabled(false);
    m_buttons[FourthButton]->setEnabled(true);

    char secondPipe[] = {'b'};

    m_manager->sendStartToPipeline(secondPipe);

    QString event{"Start second pipeline"};
    QString dataTime = m_manager->getDataTime();

    emit sendData(event, dataTime);
}

void ManualControlWindow::on_pushButtonThirdClicked()
{
    //when we click button we making this button invisible
    m_buttons[ThirdButton]->setEnabled(false);
    m_buttons[FourthButton]->setEnabled(true);

    char thirdPipe[] = {'c'};

    m_manager->sendStartToPipeline(thirdPipe);

    QString event{"Start third pipeline"};
    QString dataTime = m_manager->getDataTime();

    emit sendData(event, dataTime);
}

void ManualControlWindow::on_pushButtonStopClicked()
{
    //when we click stop button, other buttons is visible
    //and stop button becomes invisible
    m_buttons[FourthButton]->setEnabled(false);
    m_buttons[FirstButton]->setEnabled(true);
    m_buttons[SecondButton]->setEnabled(true);
    m_buttons[ThirdButton]->setEnabled(true);

    char stopCommands[3] = {'x', 'y', 'z'};

    m_manager->sendStopToPipeline(stopCommands);

    QString event{"Stop all pipelines"};
    QString dataTime = m_manager->getDataTime();

    emit sendData(event, dataTime);
}

void ManualControlWindow::setColorButton()
{
    //setting the color for button
    QPalette palFirst = m_buttons[FirstButton]->palette();
    palFirst.setColor(QPalette::Button, QColor(Qt::green));
    m_buttons[FirstButton]->setAutoFillBackground(true);
    m_buttons[FirstButton]->setPalette(palFirst);
    m_buttons[FirstButton]->update();

    QPalette palSecond = m_buttons[SecondButton]->palette();
    palSecond.setColor(QPalette::Button, QColor(Qt::green));
    m_buttons[SecondButton]->setAutoFillBackground(true);
    m_buttons[SecondButton]->setPalette(palSecond);
    m_buttons[SecondButton]->update();

    QPalette palThird = m_buttons[ThirdButton]->palette();
    palThird.setColor(QPalette::Button, QColor(Qt::green));
    m_buttons[ThirdButton]->setAutoFillBackground(true);
    m_buttons[ThirdButton]->setPalette(palThird);
    m_buttons[ThirdButton]->update();

    QPalette palFourth = m_buttons[FourthButton]->palette();
    palFourth.setColor(QPalette::Button, QColor(Qt::red));
    m_buttons[FourthButton]->setAutoFillBackground(true);
    m_buttons[FourthButton]->setPalette(palFourth);
    m_buttons[FourthButton]->update();

}



