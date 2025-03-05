#include "msghandle.h"
#include"operatedb.h"
#include"mytcpserver.h"
#include"server.h"
#include<QDir>
MsgHandle::MsgHandle()
{
    m_bUpload=false;
}

PDU *MsgHandle::regist(PDU *pdu)
{
    char user_name[32]={'\0'};
    char user_pwd[32]={'\0'};
    memcpy(user_name,pdu->caData,32);
    memcpy(user_pwd,pdu->caData+32,32);

    bool ret=operateDB::GetInstance().handleRegist(user_name,user_pwd);
    if(ret){
        QDir dir;
        qDebug()<<"root path:"<<QString("%1/%2").arg(server::GetInstance().m_filerootPath).arg(user_name);
        dir.mkdir(QString("%1/%2").arg(server::GetInstance().m_filerootPath).arg(user_name));
    }

    PDU* retpdu=makePDU(0);
    retpdu->uiMsgType=ENUM_MSG_TYPE_REGIST_RESPOND;
    memcpy(retpdu->caData,&ret,sizeof(bool));
    return retpdu;
}

PDU *MsgHandle::login(PDU *pdu, QString &m_name)
{
    char user_name[32]={'\0'};
    char user_pwd[32]={'\0'};
    memcpy(user_name,pdu->caData,32);
    memcpy(user_pwd,pdu->caData+32,32);
    bool ret=operateDB::GetInstance().handleLogin(user_name,user_pwd);;
    PDU* retpdu=makePDU(0);
    retpdu->uiMsgType=ENUM_MSG_TYPE_LOGIN_RESPOND;
    memcpy(retpdu->caData,&ret,sizeof(bool));
    m_name=user_name;
    return retpdu;
}

PDU *MsgHandle::searchUser(PDU *pdu)
{
    char user_name[32]={'\0'};
    memcpy(user_name,pdu->caData,32);

    int ret=operateDB::GetInstance().handleSearchUser(user_name);

    PDU* retpdu=makePDU(0);
    retpdu->uiMsgType=ENUM_MSG_TYPE_SEARCH_USER_RESPOND;
    memcpy(retpdu->caData,user_name,32);
    memcpy(retpdu->caData+32,&ret,32);
    return retpdu;
}

PDU *MsgHandle::onlineUser()
{
    QStringList res=operateDB::GetInstance().getOnlineUser();
    uint resLen=res.size()*32;
    PDU* retpdu=makePDU(resLen);
    retpdu->uiMsgType=ENUM_MSG_TYPE_ONLINE_USER_RESPOND;
    for(int i=0;i<res.size();i++){
        memcpy(retpdu->caMsg+i*32,res.at(i).toStdString().c_str(),32);
    }
    return retpdu;
}

PDU *MsgHandle::addFriend(PDU *pdu)
{
    char curname[32]={'\0'};
    char tarname[32]={'\0'};
    memcpy(curname,pdu->caData,32);
    memcpy(tarname,pdu->caData+32,32);
    int ret=operateDB::GetInstance().handleAddFriend(curname,tarname);
    if(ret==1){
        MyTcpServer::GetInstance().resand(tarname,pdu);
    }
    PDU* retpdu=makePDU(0);
    retpdu->uiMsgType=ENUM_MSG_TYPE_ADD_FRIEND_RESPOND;
    memcpy(retpdu->caData,&ret,sizeof(int));
    return retpdu;

}

PDU *MsgHandle::addFriendAgree(PDU *pdu)
{
    char curname[32]={'\0'};
    char tarname[32]={'\0'};
    memcpy(curname,pdu->caData,32);
    memcpy(tarname,pdu->caData+32,32);
    operateDB::GetInstance().handleAddFriendAgree(curname,tarname);
    PDU* retpdu=makePDU(0);
    retpdu->uiMsgType=ENUM_MSG_TYPE_ADD_FRIEND_AGREE_RESPOND;
    MyTcpServer::GetInstance().resand(curname,retpdu);
    return retpdu;

}

void MsgHandle::addFriendRefuse(PDU *pdu)
{

    char name[32]={'\0'};
    memcpy(name,pdu->caData,32);
    PDU* retpdu=makePDU(0);
    memcpy(retpdu->caData,pdu->caData+32,32);

    retpdu->uiMsgType=ENUM_MSG_TYPE_ADD_FRIEND_REFUSE_RESPOND;
    MyTcpServer::GetInstance().resand(name,retpdu);

}

PDU *MsgHandle::flushFriend(PDU *pdu)
{
    qDebug()<<"服务器接收到PDU准备处理刷新好友";
    QStringList res=operateDB::GetInstance().handleFlushFriend(pdu->caData);
    uint resLen=res.size()*32;
    PDU* retpdu=makePDU(resLen);
    retpdu->uiMsgType=ENUM_MSG_TYPE_FLUSH_FRIEND_RESPOND;
    for(int i=0;i<res.size();i++){
        memcpy(retpdu->caMsg+i*32,res.at(i).toStdString().c_str(),32);
    }

    return retpdu;
}

PDU *MsgHandle::delFriend(PDU *pdu)
{
    qDebug()<<"服务器接收到删除好友请求";
    char curname[32]={'\0'};
    char tarname[32]={'\0'};
    memcpy(curname,pdu->caData,32);
    memcpy(tarname,pdu->caData+32,32);
    bool ret=operateDB::GetInstance().handleDelFriend(curname,tarname);
    PDU* retpdu=makePDU(0);
    memcpy(retpdu->caData,&ret,32);
    retpdu->uiMsgType=ENUM_MSG_TYPE_DEL_FRIEND_RESPOND;
    return retpdu;
}

PDU *MsgHandle::mkdir(PDU *pdu)
{
    char dirname[32]={'\0'};
    memcpy(dirname,pdu->caData,32);
    QDir dir;
    bool ret=0;
    QString strCurPath=pdu->caMsg;
    QString dirPath=QString("%1/%2").arg(pdu->caMsg).arg(dirname);
    if(dir .exists(dirPath)||!dir.exists(strCurPath)){
        ret=0;
    }else{
        dir.mkdir(dirPath);
        ret=1;
    }
    PDU* retpdu=makePDU(0);
    memcpy(retpdu->caData,&ret,32);
    retpdu->uiMsgType=ENUM_MSG_TYPE_MKDIR_RESPOND;
    return retpdu;
}


void MsgHandle::chat(PDU *pdu)
{
    qDebug()<<"服务器处理客户端聊天";
    char tarname[32]={'\0'};
    memcpy(tarname,pdu->caData+32,32);
    pdu->uiMsgType=ENUM_MSG_TYPE_CHAT_RESPOND;
    qDebug()<<"两个用户"<<pdu->caData<<"and"<<pdu->caData+32<<"消息内容"<<pdu->caMsg;
    MyTcpServer::GetInstance().resand(tarname,pdu);

}

PDU *MsgHandle::flushFile(PDU *pdu)
{
    QDir dir(pdu->caMsg);
    QFileInfoList FileInfoList=dir.entryInfoList();//获取dir下的所有文件

    int iFileCount=FileInfoList.size();
    PDU* respdu=makePDU((iFileCount-2)*sizeof(FileInfo));//构建PDU,大小为文件数量*FileInfo大小
    respdu->uiMsgType=ENUM_MSG_TYPE_FLUSH_FILE_RESPOND;
    FileInfo* pFileInfo=NULL;
    QString FileName;
    //遍历文件列表
    for(int i=0, j=0;i<iFileCount;i++){
        FileName=FileInfoList[i].fileName();
        if(FileName=="."||FileName==".."){
            continue;
        }
        pFileInfo=(FileInfo*)respdu->caMsg+j++;//将caMsg指针转化为FileInfo类型指针,此时两者地址就是一样的,记得要指针偏移
        //填充pFileInfo
        memcpy(pFileInfo->caName,FileName.toStdString().c_str(),FileName.size());
        if(FileInfoList[i].isDir()){
            pFileInfo->iFileType=0;
        }else if(FileInfoList[i].isFile()){
            pFileInfo->iFileType=1;
        }
    }
    return respdu;
}

PDU *MsgHandle::delDir(PDU *pdu)
{
    char* dirpath=pdu->caMsg;
    QFileInfo pfileInfo(dirpath);
    bool ret=0;
    if(pfileInfo.isDir()){
        QDir dir;
        dir.setPath(dirpath);
        ret=dir.removeRecursively();

    }
    PDU* retpdu=makePDU(0);
    memcpy(retpdu->caData,&ret,32);
    retpdu->uiMsgType=ENUM_MSG_TYPE_DELDIR_RESPOND;
    return retpdu;
}

PDU *MsgHandle::delFile(PDU *pdu)
{
    char* filepath=pdu->caMsg;
    QFileInfo pfileInfo(filepath);
    bool ret=0;
    if(pfileInfo.isFile()){
        QFile f;
        ret=f.remove(filepath);

    }
    PDU* retpdu=makePDU(0);
    memcpy(retpdu->caData,&ret,32);
    retpdu->uiMsgType=ENUM_MSG_TYPE_DELFILE_RESPOND;
    return retpdu;
}

PDU *MsgHandle::renameFile(PDU *pdu)
{
    qDebug()<<"服务器接收到重复名文件请求";
    QString newFileName=pdu->caData;
    QString oldFileName=pdu->caData+32;
    QString FilePath=pdu->caMsg;
    QString newFilePath=QString("%1/%2").arg(FilePath).arg(newFileName);
    QString oldFilePath=QString("%1/%2").arg(FilePath).arg(oldFileName);
    QDir dir;
    bool ret=dir.rename(oldFilePath,newFilePath);
    PDU* retpdu=makePDU(0);
    memcpy(retpdu->caData,&ret,32);
    retpdu->uiMsgType=ENUM_MSG_TYPE_RENAME_FILE_RESPOND;
    return retpdu;

}

PDU *MsgHandle::mvFile(PDU *pdu)
{
    int srcLen=0;
    int tarLen=0;
    memcpy(&srcLen,pdu->caData,sizeof(int));
    memcpy(&tarLen,pdu->caData+sizeof(int),sizeof(int));
    char* srcPath=new char[srcLen+1];
    char* tarPath=new char[tarLen+1];
    memset(srcPath,'\0',srcLen+1);
    memset(tarPath,'\0',tarLen+1);
    memcpy(srcPath,pdu->caMsg,srcLen);
    memcpy(tarPath,pdu->caMsg+srcLen+1,tarLen);
    qDebug()<<"srcPath:"<<srcPath<<"tarpath"<<tarPath;
    bool ret=QFile::rename(srcPath,tarPath);
    PDU* retpdu=makePDU(0);
    memcpy(retpdu->caData,&ret,32);
    retpdu->uiMsgType=ENUM_MSG_TYPE_MOVE_FILE_RESPOND;
    delete[] srcPath;
    srcPath=NULL;
    delete[] tarPath;
    tarPath=NULL;
    return retpdu;
}

PDU *MsgHandle::uploadFile(PDU *pdu)
{
    qDebug()<<"服务器接收到上传文件请求";
    PDU* retpdu=makePDU(0);
    retpdu->uiMsgType=ENUM_MSG_TYPE_UP_FILE_RESPOND;
    int ret=0;
    //已有文件上传返回1
    if(m_bUpload==1){
        ret=1;
        memcpy(retpdu->caData,&ret,32);
        return retpdu;
    }
    //取出文件和路径并拼接
    char caFileName[32]={'\0'};
    qint64 fileSize=0;
    memcpy(caFileName,pdu->caData,32);
    memcpy(&fileSize,pdu->caData+32,sizeof(qint64));
    QString strPath=QString("%1/%2").arg(pdu->caMsg).arg(caFileName);
    m_fUploadFile.setFileName(strPath);
    //打开文件成功返回属性,失败返回-1
    if(m_fUploadFile.open(QIODevice::WriteOnly)){
        m_iUploadTotal=fileSize;
        m_iUploadReceived=0;
        m_bUpload=true;
    }else{
        ret=-1;
    }
    memcpy(retpdu->caData,&ret,sizeof(int));
    return retpdu;
}

PDU *MsgHandle::uploadFileData(PDU *pdu)
{
    qDebug()<<"服务器接收到上传文件数据请求";
    m_fUploadFile.write(pdu->caMsg,pdu->uiMsgLen);
    m_iUploadReceived+=pdu->uiMsgLen;
    if(m_iUploadReceived<m_iUploadTotal) return NULL;
    m_bUpload=false;
    m_fUploadFile.close();
    PDU* respdu=makePDU(0);
    respdu->uiMsgType=ENUM_MSG_TYPE_UP_FILE_DATA_RESPOND;
    bool ret=m_iUploadTotal==m_iUploadReceived;
    memcpy(respdu->caData,&ret,32);
    return respdu;
}

PDU *MsgHandle::shareFile(PDU *pdu)
{
    qDebug()<<"服务器接收到分享文件请求";
    char strCurName[32]={'\0'};
    int friendNum=0;
    memcpy(&strCurName,pdu->caData,32);
    memcpy(&friendNum,pdu->caData+32,sizeof (int));
    int size=friendNum*32;

    PDU* resandpdu=makePDU(pdu->uiMsgLen-size);

    resandpdu->uiMsgType=pdu->uiMsgType;

    memcpy(resandpdu->caData,strCurName,32);
    qDebug()<<"11"<<pdu->caMsg+size<<"and"<<pdu->uiMsgLen-size;
    memcpy(resandpdu->caMsg,pdu->caMsg+size,pdu->uiMsgLen-size);
    char caRecvName[32]={'\0'};
    for(int i=0;i<friendNum;i++){
        memcpy(caRecvName,pdu->caMsg+i*32,32);
        MyTcpServer::GetInstance().resand(caRecvName,resandpdu);
    }
    free(resandpdu);
    resandpdu=NULL;

    PDU* respdu=makePDU(0);
    respdu->uiMsgType=ENUM_MSG_TYPE_SHARE_FILE_RESPOND;
    qDebug()<<"11111111111111111111111111";
    return respdu;
}

PDU *MsgHandle::shareFileAgree(PDU *pdu)
{
    qDebug()<<"服务器接收到分享文件同意请求";
    QString strRecvPath=QString("%1/%2").arg(server::GetInstance().m_filerootPath).arg(pdu->caData);
    QString strShareFilePath =pdu->caMsg;
    int index=strShareFilePath.lastIndexOf('/');
    QString strFileName=strShareFilePath.right(strShareFilePath.size()-index-1);
    qDebug()<<"strFileName:"<<strFileName;
    strRecvPath=strRecvPath+"/"+strFileName;
     QFileInfo fileInfo(strShareFilePath);

    bool ret =true;
    if(fileInfo.isFile()){
        ret=QFile::copy(strShareFilePath,strRecvPath);
    }else if(fileInfo.isDir()){
        qDebug()<<"strShareFilePath"<<strShareFilePath<<"strShareFilePath"<<strRecvPath;
        ret=copyDir(strShareFilePath,strRecvPath);
    }
    PDU* respdu=makePDU(0);
    respdu->uiMsgType=ENUM_MSG_TYPE_SHARE_FILE_AGREE_ESPOND;
    memcpy(respdu->caData,&ret,32);
    return respdu;
}

bool MsgHandle::copyDir(QString strSourcePath, QString strTargetPath)
{
    QDir dir;
    dir.mkdir(strTargetPath);
    dir.setPath(strSourcePath);
    QFileInfoList fileInfoList=dir.entryInfoList();
    bool ret=true;
    QString srcTmp;
    QString destTmp;
    for(int i=0;i<fileInfoList.size();i++){
        if(fileInfoList[i].isFile()){
            srcTmp=strSourcePath+ '/' +fileInfoList[i].fileName();
            destTmp=strTargetPath+'/'+fileInfoList[i].fileName();
            if(!QFile::copy(srcTmp,destTmp)){
                ret=false;
            }
        }else if(fileInfoList[i].isDir()){
            if(fileInfoList[i].fileName()==QString(".")||fileInfoList[i].fileName()==QString("..")){
                continue;
            }
            srcTmp=strSourcePath+ '/' +fileInfoList[i].fileName();
            destTmp=strTargetPath+'/'+fileInfoList[i].fileName();
            if(!copyDir(srcTmp,destTmp)){
                ret=false;
            }
        }
    }
    return ret;
}












