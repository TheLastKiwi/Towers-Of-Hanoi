#include "hanoiwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HanoiWindow w;
    w.show();

    return a.exec();
}
