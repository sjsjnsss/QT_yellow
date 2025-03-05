#include "server.h"
#include"operatedb.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    operateDB::GetInstance().connect();
    server w;
    w.show();
    return a.exec();
}
