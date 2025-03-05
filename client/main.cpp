#include "client.h"
#include"friend.h"
#include"index.h"
#include"file.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    client::GetInstance().show();

    return a.exec();
}
