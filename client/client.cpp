#include "client.h"
#include "ui_client.h"
#include"reshandler.h"
client::client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
{
    ui->setupUi(this);
    //加载配置文件
    loadconfig();
    //关联信号槽和槽函数
    connect(&m_tcpsocket,&QTcpSocket::connected,this,&client::showConnect);
    connect(&m_tcpsocket,&QTcpSocket::readyRead,this,&client::recvMsg);
    //与服务器建立连接
    m_tcpsocket.connectToHost(QHostAddress(m_strIP),m_usport);
    m_prh=new resHandler;
}

client::~client()
{
    delete ui;
    delete m_prh;
}




void client::loadconfig()
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

QTcpSocket &client::GetSocket()
{
    return m_tcpsocket;
}



PDU *client::handleRes(PDU *pdu)
{
    qDebug()<<"客户端接收到消息类型:"<<pdu->caData<<"消息内容:"<<pdu->caMsg<<"PDU大小:"<<pdu->uiPDULen<<"协议类型:"<<pdu->uiMsgType;
    switch (pdu->uiMsgType) {
    case ENUM_MSG_TYPE_REGIST_RESPOND:{
        m_prh->regist(pdu);
        break;

    }
    case ENUM_MSG_TYPE_LOGIN_RESPOND:{
        m_prh->login(pdu);
        break;

    }
    case ENUM_MSG_TYPE_SEARCH_USER_RESPOND:{
        m_prh->searchUser(pdu);
        break;

    }
    case ENUM_MSG_TYPE_ONLINE_USER_RESPOND:{
        m_prh->onlineUser(pdu);
        break;

    }
    case ENUM_MSG_TYPE_ADD_FRIEND_RESPOND:{
        m_prh->addFriend(pdu);
        break;

    }
    case ENUM_MSG_TYPE_ADD_FRIEND_REQUIST:{
        m_prh->addFriendRequest(pdu);

        break;

    }
    case ENUM_MSG_TYPE_ADD_FRIEND_AGREE_RESPOND:{
        m_prh->addFriendAgree();
        break;

    }
    case ENUM_MSG_TYPE_ADD_FRIEND_REFUSE_RESPOND:{
        m_prh->addFriendRefuse(pdu);
        break;

    }
    case ENUM_MSG_TYPE_FLUSH_FRIEND_RESPOND:{
        m_prh->flushFriend(pdu);
        break;

    }
    case ENUM_MSG_TYPE_DEL_FRIEND_RESPOND:{
        m_prh->delFriend(pdu);
        break;

    }
    case ENUM_MSG_TYPE_CHAT_RESPOND:{
        m_prh->chat(pdu);
        break;

    }
    case ENUM_MSG_TYPE_MKDIR_RESPOND:{
        m_prh->mkdir(pdu);
        break;

    }
    case ENUM_MSG_TYPE_FLUSH_FILE_RESPOND:{
        m_prh->flushFile(pdu);
        break;

    }
    case ENUM_MSG_TYPE_DELDIR_RESPOND:{
        m_prh->delDir(pdu);
        break;

    }
    case ENUM_MSG_TYPE_DELFILE_RESPOND:{
        m_prh->delFile(pdu);
        break;

    }
    case ENUM_MSG_TYPE_RENAME_FILE_RESPOND:{
        m_prh->renameFile(pdu);
        break;

    }
    case ENUM_MSG_TYPE_MOVE_FILE_RESPOND:{
        m_prh->moveFile(pdu);
        break;

    }
    case ENUM_MSG_TYPE_UP_FILE_RESPOND:{
        m_prh->uploadFile(pdu);
        break;

    }
    case ENUM_MSG_TYPE_UP_FILE_DATA_RESPOND:{
        m_prh->uploadFileData(pdu);
        break;

    }
    case ENUM_MSG_TYPE_SHARE_FILE_RESPOND:{
        m_prh->shareFile(pdu);
        break;

    }
    case ENUM_MSG_TYPE_SHARE_FILE_REQUIST:{
        m_prh->shareFileRequest(pdu);
        break;

    }
    case ENUM_MSG_TYPE_SHARE_FILE_AGREE_ESPOND:{
        m_prh->shareFileAgree(pdu);
        break;

    }
    default:
        break;
    }
    return pdu;
}

void client::showConnect()
{
    qDebug()<<"连接服务器成功";
}




void client::recvMsg()
{

    QByteArray data=m_tcpsocket.readAll();
    buffer.append(data);
    while(buffer.size()>=int(sizeof(PDU))){
        PDU* pdu=(PDU*)buffer.data();
        if(buffer.size()<int(pdu->uiPDULen)){
            break;
        }

        handleRes(pdu);
        buffer.remove(0,pdu->uiPDULen);
    }
}

client &client::GetInstance()
{
    static client Instance;
    return Instance;
}

void client::on_regist_PB_clicked()
{
    QString user_msg=ui->user_LE->text();
    QString user_pwd=ui->pwd_LE->text();
    if(user_msg==NULL||user_pwd==NULL){
        QMessageBox::critical(this,"注册失败","用户名或密码不能为空");
        return;
    }
    PDU* pdu=makePDU(0);
    pdu->uiMsgType=ENUM_MSG_TYPE_REGIST_REQUEST;
    memcpy(pdu->caData,user_msg.toStdString().c_str(),32);
    memcpy(pdu->caData+32,user_pwd.toStdString().c_str(),32);
    m_tcpsocket.write((char*)pdu,pdu->uiPDULen);

    free(pdu);
    pdu=NULL;

}

void client::on_login_PB_clicked()
{
    QString user_msg=ui->user_LE->text();
    QString user_pwd=ui->pwd_LE->text();
    if(user_msg==NULL||user_pwd==NULL){
        QMessageBox::critical(this,"登录失败","用户名或密码不能为空");
        return;
    }
    PDU* pdu=makePDU(0);
    pdu->uiMsgType=ENUM_MSG_TYPE_LOGIN_REQUIST;
    memcpy(pdu->caData,user_msg.toStdString().c_str(),32);
    memcpy(pdu->caData+32,user_pwd.toStdString().c_str(),32);
    m_tcpsocket.write((char*)pdu,pdu->uiPDULen);
    Login_name=user_msg;
    free(pdu);
    pdu=NULL;

}
