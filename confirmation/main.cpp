#include "confirm.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    confirm w;
    w.show();
    return a.exec();
}
