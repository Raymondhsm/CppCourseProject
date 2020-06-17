#include "game.h"
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    game w;
    //setTitle
    w.setWindowTitle("Slider Football");
    w.menu();
    w.show();
    return a.exec();
}
