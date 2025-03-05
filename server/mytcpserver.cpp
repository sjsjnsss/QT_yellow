#include "mytcpserver.h"



MyTcpServer::MyTcpServer()
{


}


MyTcpServer &MyTcpServer::GetInstance()
{
    static MyTcpServer Instance;
    return Instance;
}

void MyTcpServer::resand(char* strTarName, PDU *pdu)
{

    if(strTarName==NULL||pdu==NULL) return;
    for(int i=0;i<m_TcpSocket.size();i++){
        if(m_TcpSocket.at(i)->m_name==strTarName){
            qDebug()<<"给谁返回了"<<strTarName;
            m_TcpSocket.at(i)->write((char*)pdu,pdu->uiPDULen);
            break;
        }
    }
}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"新的客户端连接";
    MyTcpSocket* pTcpsocket=new MyTcpSocket;
    pTcpsocket->setSocketDescriptor(socketDescriptor);
    m_TcpSocket.append(pTcpsocket);
    for(int i=0;i<m_TcpSocket.size();i++){
        qDebug()<<m_TcpSocket.at(i);
    }
    connect(pTcpsocket,&MyTcpSocket::offline,this,&MyTcpServer::deleteClient);
}

void MyTcpServer::deleteClient(MyTcpSocket *mysocket)
{
    m_TcpSocket.removeOne(mysocket);
    mysocket->deleteLater();
    mysocket=NULL;

    for(int i=0;i<m_TcpSocket.size();i++){
        qDebug()<<"服务器在线用户列表"<<m_TcpSocket.at(i)->m_name;
    }
}






