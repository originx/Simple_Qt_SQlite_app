#include <QtGui/QApplication>
#include "glavniprozor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GlavniProzor w;
    w.show();

    return a.exec();
}
