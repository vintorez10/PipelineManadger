#include "pipelinemanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PipelineManager w;
    w.setMinimumSize(800, 400);
    w.show();
    return a.exec();
}
