#include "verifier.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Verifier w;
    w.show();

    return a.exec();
}
