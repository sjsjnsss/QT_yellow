#include "reshandler.h"
#include"client.h"
#include"index.h"
#include<QMessageBox>
#include<QDebug>
#include<QString>
void resHandler::regist(PDU* pdu)
{
    qDebug()<<"客户端接收到服务器的注册回应";
    bool ret=0;
    memcpy(&ret,pdu->caData,sizeof(bool));

    if(ret){
        QMessageBox::information(&client::GetInstance(),"注册","注册成功");
    }
    else  QMessageBox::information(&client::GetInstance(),"注册","注册失败:用户名或密码非法");
}

void resHandler::login(PDU *pdu)
{
    qDebug()<<"客户端接收到服务器的登录回应";
    bool ret=0;
    memcpy(&ret,pdu->caData,sizeof(bool));
    if(ret){
        Index::GetInstance().show();
        client::GetInstance().hide();
    }
    else  QMessageBox::information(&client::GetInstance(),"登录","登录失败");
}

void resHandler::searchUser(PDU *pdu)
{
    qDebug()<<"客户端接收到服务器的查询好友回应";
    char name[32]={'\0'};
    int ret=0;

    QString showMsg;
    memcpy(name,pdu->caData,32);
    memcpy(&ret,pdu->caData+32,32);
    if(ret==1){
        showMsg=QString("%1 在线").arg(name);
        int res=QMessageBox::information(Index::GetInstance().getFriend(),"添加好友",showMsg,"添加好友","取消");
        if(res!=0) return;
        QString strCurName = client::GetInstance().Login_name;
        QString strTarName=name;
        PDU* pdu=makePDU(0);
        pdu->uiMsgType=ENUM_MSG_TYPE_ADD_FRIEND_REQUIST;
        memcpy(pdu->caData,strCurName.toStdString().c_str(),32);
        memcpy(pdu->caData+32,name,32);
        client::GetInstance().GetSocket().write((char*)pdu,pdu->uiPDULen);
        free(pdu);
        pdu=NULL;
        return;
    }

    if(ret==0){
        showMsg=QString("%1 不在线").arg(name);
    }
    else{
        showMsg=QString("%1 不存在").arg(name);
    }
    QMessageBox::information(Index::GetInstance().getFriend(),"查询",showMsg);
}

void resHandler::onlineUser(PDU *pdu)
{
    qDebug()<<"客户端接收到服务器的在线好友回应";
    char name[32]={'\0'};
    QStringList userlist;
    uint size=pdu->uiMsgLen/32;
    for (uint i=0;i<size;i++) {
       memcpy(name,pdu->caMsg+i*32,32);
       if(QString(name)==client::GetInstance().Login_name){
           continue;
       }
       userlist.append(QString(name));
    }
    Index::GetInstance().getFriend()->m_pOnlineUser->showOnlineUser(userlist);
}

void resHandler::addFriend(PDU *pdu)
{//-1:报错  -2:已经是好友  1:在线  0:不在线
    qDebug()<<"客户端接收到服务器的添加好友回应";
    int ret=-1;
    QString showMsg;
    memcpy(&ret,pdu->caData,32);
    if(ret==-1){
        showMsg="报错";
    }else if(ret==-2){
        showMsg="已经是好友";
    }else if(ret==1){
        showMsg="等待对方同意....";
    }else{
        showMsg="对方不在线";
    }

    QMessageBox::information(Index::GetInstance().getFriend(),"添加好友",showMsg);

}

void resHandler::addFriendRequest(PDU *pdu)
{
    char name[32]={'\0'};
    memcpy(name,pdu->caData,32);
    int ret=QMessageBox::question(Index::GetInstance().getFriend(),"添加好友",QString("'%1'请求添加好友,是否同意请求?").arg(name));
    if(ret==QMessageBox::No){
        //不同意添加
        PDU* retpdu=makePDU(0);
        memcpy(retpdu->caData,pdu->caData,32);
        memcpy(retpdu->caData+32,pdu->caData+32,32);
        retpdu->uiMsgType=ENUM_MSG_TYPE_ADD_FRIEND_REFUSE_REQUIST;
        client::GetInstance().GetSocket().write((char*)retpdu,retpdu->uiPDULen);
        qDebug()<<"两个用户名"<<retpdu->caData<<"and"<<retpdu->caData+32;
        free(retpdu);
        retpdu=NULL;
       return ;
    }

    PDU* retpdu=makePDU(0);
    memcpy(retpdu->caData,pdu->caData,64);
    retpdu->uiMsgType=ENUM_MSG_TYPE_ADD_FRIEND_AGREE_REQUIST;
    client::GetInstance().GetSocket().write((char*)retpdu,retpdu->uiPDULen);
    free(retpdu);
    retpdu=NULL;
    return;
}

void resHandler::addFriendAgree()
{

    QMessageBox::information(Index::GetInstance().getFriend(),"添加好友","添加成功");
}

void resHandler::addFriendRefuse(PDU *pdu)
{
    qDebug()<<"客户端接收到拒绝添加好友回应";
    char name[32]={'\0'};
    memcpy(name,pdu->caData,32);
    QMessageBox::information(Index::GetInstance().getFriend(),"添加好友",QString("'%1'拒绝添加好友").arg(name));
}

void resHandler::flushFriend(PDU *pdu)
{
    qDebug()<<"客户端接收到服务器的刷新好友回应";
    char name[32]={'\0'};
    QStringList userlist;
    uint size=pdu->uiMsgLen/32;
    for (uint i=0;i<size;i++) {
       memcpy(name,pdu->caMsg+i*32,32);
       userlist.append(QString(name));
    }
    Index::GetInstance().getFriend()->showflushFriend(userlist);
}

void resHandler::delFriend(PDU *pdu)
{
    qDebug()<<"客户端接收到服务器的删除好友回应";
    bool ret=0;
    memcpy(&ret,pdu->caData,sizeof(bool));
    if(ret){
        QMessageBox::information(&client::GetInstance(),"删除好友","删除好友成功");
    }
    else  QMessageBox::information(&client::GetInstance(),"删除好友","删除好友失败");
    Index::GetInstance().getFriend()->flushFriend();
}

void resHandler::chat(PDU *pdu)
{
    char cachatname[32]={'\0'};
    memcpy(cachatname,pdu->caData,32);
    qDebug()<<"客户端接收到服务器的聊天回应";
    Chat* c=Index::GetInstance().getFriend()->m_pChat;
    if(c->isHidden()){
        c->show();
        c->m_strChatName=cachatname;
    }
    c->updateShow_TE(QString(" %1 : %2").arg(cachatname).arg(pdu->caMsg));
}

void resHandler::mkdir(PDU *pdu)
{
    qDebug()<<"客户端接收到服务器的创建文件夹回应";
    bool ret=0;
    memcpy(&ret,pdu->caData,sizeof(bool));
    if(ret){
        Index::GetInstance().getFile()->flushFile();
    }
    else  QMessageBox::information(&client::GetInstance(),"创建文件夹","创建文件夹失败");
}

void resHandler::flushFile(PDU *pdu)
{
    QList<FileInfo*> pFileList;
    int count=pdu->uiMsgLen/sizeof(FileInfo);
    for(int i=0;i<count;i++){
        FileInfo* pFileInfo=new FileInfo;
        memcpy(pFileInfo,pdu->caMsg+i*sizeof(FileInfo),sizeof(FileInfo));
        pFileList.append(pFileInfo);
    }
    Index::GetInstance().getFile()->updateFile(pFileList);
}

void resHandler::delDir(PDU *pdu)
{
    bool ret=0;
    memcpy(&ret,pdu->caData,32);
    if(ret==0){
        QMessageBox::warning(Index::GetInstance().getFile(),"删除文件夹","删除失败");
    }
    Index::GetInstance().getFile()->flushFile();
}

void resHandler::delFile(PDU *pdu)
{
    bool ret=0;
    memcpy(&ret,pdu->caData,32);
    if(ret==0){
        QMessageBox::warning(Index::GetInstance().getFile(),"删除文件","删除失败");
    }
    Index::GetInstance().getFile()->flushFile();
}

void resHandler::renameFile(PDU *pdu)
{
    qDebug()<<"客户端接收到重复名文件回应";
    bool ret=0;
    memcpy(&ret,pdu->caData,32);
    if(ret==0){
        QMessageBox::warning(Index::GetInstance().getFile(),"重复名文件","重复名文件失败");
    }
    Index::GetInstance().getFile()->flushFile();
}

void resHandler::moveFile(PDU *pdu)
{
    qDebug()<<"客户端接收到移动文件回应";
    bool ret=0;
    memcpy(&ret,pdu->caData,32);
    if(ret==0){
        QMessageBox::warning(Index::GetInstance().getFile(),"移动文件","移动文件失败");
    }
    Index::GetInstance().getFile()->flushFile();
}

void resHandler::uploadFile(PDU *pdu)
{
    qDebug()<<"客户端接收到上传文件回应";
    int ret=0;
    memcpy(&ret,pdu->caData,32);
    if(ret==1){
        QMessageBox::warning(Index::GetInstance().getFile(),"上传文件","已有文件正在上传");
        return;
    }
    else if(ret==-1){
        QMessageBox::warning(Index::GetInstance().getFile(),"上传文件","上传文件失败");
        return;
    }else{
        Index::GetInstance().getFile()->uploadFile();
    }
}

void resHandler::uploadFileData(PDU *pdu)
{
    qDebug()<<"客户端接收到上传文件数据回应";
    bool ret=0;
    memcpy(&ret,pdu->caData,32);
    if(ret==0){
        QMessageBox::warning(Index::GetInstance().getFile(),"上传文件","上传文件失败");
    }
    Index::GetInstance().getFile()->flushFile();
    Index::GetInstance().getFile()->bUpload=false;
}

void resHandler::shareFile(PDU *pdu)
{
    QMessageBox::information(Index::GetInstance().getFile()->sharefile,"分享文件","分享文件成功");
}

void resHandler::shareFileRequest(PDU *pdu)
{
    QString recMsg=QString("%1 分享文件 %2 是否接收?").arg(pdu->caData).arg(pdu->caMsg);
    int ret=QMessageBox::question(Index::GetInstance().getFile()->sharefile,"分享文件",recMsg);
    if(ret==QMessageBox::No){
        return;
    }
    PDU* respdu=makePDU(pdu->uiMsgLen);
    respdu->uiMsgType=ENUM_MSG_TYPE_SHARE_FILE_AGREE_REQUIST;
    memcpy(respdu->caData,client::GetInstance().Login_name.toStdString().c_str(),32);
    memcpy(respdu->caMsg,pdu->caMsg,pdu->uiMsgLen);
    client::GetInstance().GetSocket().write((char*)respdu,respdu->uiPDULen);
    free(respdu);
    respdu=NULL;
}

void resHandler::shareFileAgree(PDU *pdu)
{
    qDebug()<<"客户端接收到分享文件同意回应";
    bool ret=0;
    memcpy(&ret,pdu->caData,32);
    if(ret==0){
        QMessageBox::warning(Index::GetInstance().getFile(),"分享文件","分享文件失败");
    }
    Index::GetInstance().getFile()->flushFile();
}

resHandler::resHandler()
{

}
