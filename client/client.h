#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include<QFile>
#include<QMessageBox>
#include<QDebug>
#include<QString>
#include<QTcpSocket>
#include<QHostAddress>
#include<QLineEdit>
#include"protocol.h"
#include"index.h"
#include"reshandler.h"
QT_BEGIN_NAMESPACE
namespace Ui { class client; }
QT_END_NAMESPACE

class client : public QMainWindow
{
    Q_OBJECT

public slots:
    void showConnect();//显示服务器和客户端是否成功连接
    //void on_pushButton_clicked();
    void recvMsg();//接收函数

public:
    static client& GetInstance();
    void loadconfig();
    QTcpSocket& GetSocket();
    PDU* handleRes(PDU* pdu);
    resHandler* m_prh;
    QByteArray buffer;
    //登录时将姓名存下来
    QString Login_name;
    QString m_filerootPath;
    ~client();
private slots:
    void on_regist_PB_clicked();

    void on_login_PB_clicked();

private:
    client(QWidget *parent = nullptr);
    client(const client& instance);
    client& operator=(const client&);
    Ui::client *ui;
    //IP和端口号
    QString m_strIP;
    quint16 m_usport;

    //和服务器建立连接
    QTcpSocket m_tcpsocket;


};
#endif // CLIENT_H
