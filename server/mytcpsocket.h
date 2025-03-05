#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include<QTcpSocket>
#include"protocol.h"
#include"operatedb.h"
#include"msghandle.h"
class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public slots:
    void close_oline();
        void recvMsg();
public:
    MyTcpSocket();

    PDU* readPDU();
    PDU* handleMsg(PDU* pdu);
    ~MyTcpSocket();
    QString m_name;//将客户端登录的姓名存下来
    QByteArray buffer;
signals:
    void offline(MyTcpSocket* mysocket);
private:
    MsgHandle* m_pmh;
};

#endif // MYTCPSOCKET_H
