#include "server.h"
#include "ui_server.h"

server::server(QWidget *parent): QWidget(parent), ui(new Ui::server){
    ui->setupUi(this);
    loadconfig();
    MyTcpServer::GetInstance().listen(QHostAddress(m_strIP),m_usport);

}

void server::loadconfig()
{
    QFile File(":/client.config");   //固定以冒号开头
    if(!File.open(QIODevice::ReadOnly)){
        QMessageBox::critical(this,"open config file","open failed");
        return;
    }
    QByteArray Data=File.readAll();
    QString strData=QString(Data);  //转化成QString类型

    QStringList List=strData.split("\r\n");   //按\r\n拆分
     m_strIP=List.at(0);
     m_usport=List.at(1).toUShort();
     m_filerootPath=List.at(2);
    qDebug()<<"加载配置信息"
           <<"IP:"<<m_strIP
           <<"port:"<<m_usport
           <<"m_filerootPath:"<<m_filerootPath;
    File.close();
}

server &server::GetInstance()
{
    static server Instance;
    return Instance;
}

server::~server()
{
    delete ui;
}

