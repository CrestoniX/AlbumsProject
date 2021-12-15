#include "mainform.h"
#include "photoform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainForm w;
    w.resize(500,300);
    w.show();
    return a.exec();
}
