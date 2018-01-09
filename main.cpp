#include "prtesterwidget.h"
#include <QApplication>
#include <QDebug>
#include "prdata.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString path = a.arguments().value(1, "./list.txt");
    if (!QFile::exists(path)) {
        path = ":/files/list.txt";
    }

    if (!PRData::instance().parseFile(path)) {
        return -1;
    }

    PRTesterWidget w;
    w.show();

    return a.exec();
}
