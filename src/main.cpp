#include "include/passerine.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Passerine w;
    w.show();

    return a.exec();
}
