#include "mytcpsocket.h"

MyTcpSocket::MyTcpSocket()
{
    connect(this,&QTcpSocket::readyRead,this,&MyTcpSocket::recvMsg);
    connect(this,&QTcpSocket::disconnected,this,&MyTcpSocket::close_oline);
    m_pmh=new MsgHandle();
}

PDU *MyTcpSocket::readPDU()
{
    uint uiPDULen=0;
    this->read((char*)&uiPDULen,sizeof(uint));//this在这里是socket
    uint uiMsgLen=uiPDULen-sizeof(PDU);
    PDU* pdu=makePDU(uiMsgLen);
    this->read((char*)pdu+sizeof(uint),uiPDULen-sizeof(uint));
    return pdu;
}

PDU *MyTcpSocket::handleMsg(PDU* pdu)
{
    qDebug()<<"handleMsg中消息类型:"<<pdu->caData<<"消息内容:"<<pdu->caMsg<<"PDU大小:"<<pdu->uiPDULen<<"协议类型:"<<pdu->uiMsgType;
    PDU* retpdu=NULL;
    switch(pdu->uiMsgType){
    case ENUM_MSG_TYPE_REGIST_REQUEST:{
        retpdu=m_pmh->regist(pdu);
        break;
        }

    case ENUM_MSG_TYPE_LOGIN_REQUIST:{
        retpdu=m_pmh->login(pdu,m_name);
        break;
        }

    case ENUM_MSG_TYPE_SEARCH_USER_REQUIST:{
    retpdu=m_pmh->searchUser(pdu);
    break;
    }
    case ENUM_MSG_TYPE_ONLINE_USER_REQUIST:{//在线用户

    retpdu=m_pmh->onlineUser();
    break;
    }
    case ENUM_MSG_TYPE_ADD_FRIEND_REQUIST:{//添加好友

    retpdu=m_pmh->addFriend(pdu);
    break;
    }
    case ENUM_MSG_TYPE_ADD_FRIEND_AGREE_REQUIST:{//同意添加

    retpdu=m_pmh->addFriendAgree(pdu);

    break;
    }
    case ENUM_MSG_TYPE_ADD_FRIEND_REFUSE_REQUIST:{//拒绝添加

    m_pmh->addFriendRefuse(pdu);

    break;
    }
    case ENUM_MSG_TYPE_FLUSH_FRIEND_REQUIST:{//刷新好友

    retpdu=m_pmh->flushFriend(pdu);

    break;
    }
    case ENUM_MSG_TYPE_DEL_FRIEND_REQUIST:{//刷新好友

    retpdu=m_pmh->delFriend(pdu);

    break;
    }
    case ENUM_MSG_TYPE_CHAT_REQUIST:{//聊天

    m_pmh->chat(pdu);

    break;
    }
    case ENUM_MSG_TYPE_MKDIR_REQUIST:{//创建文件夹

    retpdu=m_pmh->mkdir(pdu);

    break;
    }
    case ENUM_MSG_TYPE_FLUSH_FILE_REQUIST:{//刷新文件

    retpdu=m_pmh->flushFile(pdu);

    break;
    }
    case ENUM_MSG_TYPE_DELDIR_REQUIST:{//删除文件夹

    retpdu=m_pmh->delDir(pdu);

    break;
    }
    case ENUM_MSG_TYPE_DELFILE_REQUIST:{//删除文件

    retpdu=m_pmh->delFile(pdu);

    break;
    }
    case ENUM_MSG_TYPE_RENAME_FILE_REQUIST:{//重复名文件

    retpdu=m_pmh->renameFile(pdu);

    break;
    }
    case ENUM_MSG_TYPE_MOVE_FILE_REQUIST:{//移动文件

    retpdu=m_pmh->mvFile(pdu);

    break;
    }
    case ENUM_MSG_TYPE_UP_FILE_REQUIST:{//上传文件

    retpdu=m_pmh->uploadFile(pdu);

    break;
    }
    case ENUM_MSG_TYPE_UP_FILE_DATA_REQUIST:{//上传文件数据

    retpdu=m_pmh->uploadFileData(pdu);

    break;
    }
    case ENUM_MSG_TYPE_SHARE_FILE_REQUIST:{//分享文件

    retpdu=m_pmh->shareFile(pdu);

    break;
    }
    case ENUM_MSG_TYPE_SHARE_FILE_AGREE_REQUIST:{//分享文件同意

    retpdu=m_pmh->shareFileAgree(pdu);

    break;
    }



    default:
        break;
    }
    return retpdu;
}

MyTcpSocket::~MyTcpSocket()
{
    delete m_pmh;
}


void MyTcpSocket::recvMsg()
{
    QByteArray data=this->readAll();
    buffer.append(data);

    while(buffer.size()>=int(sizeof(PDU))){
        PDU* pdu=(PDU*)buffer.data();
        if(buffer.size()<int(pdu->uiPDULen)){
            break;
        }
        PDU* respdu=handleMsg(pdu);
        if(respdu) {
            write((char*)respdu,respdu->uiPDULen);
        }
        buffer.remove(0,pdu->uiPDULen);
    }

}

void MyTcpSocket::close_oline()
{
    operateDB::GetInstance().handleOffcline(m_name.toStdString().c_str());
    emit offline(this);
}


