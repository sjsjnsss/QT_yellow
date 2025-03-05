#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include<QTcpServer>
#include<QDebug>
#include"mytcpsocket.h"
class MyTcpServer : public QTcpServer
{

public slots:
    void deleteClient(MyTcpSocket* mysocket);

public:
    static MyTcpServer& GetInstance();
    void resand(char* strTarName,PDU* pdu);//转发函数,目标用户将PDU发给他
    virtual void incomingConnection(qintptr socketDescriptor);//多个客户端连接提示

private:
    QList<MyTcpSocket*> m_TcpSocket;

    MyTcpServer();
    MyTcpServer(const MyTcpServer& Instance);
    MyTcpServer& operator=(const MyTcpServer&);
};

#endif // MYTCPSERVER_H
