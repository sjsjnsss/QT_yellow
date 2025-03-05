#include<QInputDialog>
#include<QMessageBox>
#include"protocol.h"
#include "friend.h"
#include "ui_friend.h"
#include"client.h"


Friend::Friend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Friend)
{
    ui->setupUi(this);
    m_pOnlineUser=new OnlineUser;
    m_pChat=new Chat;
    flushFriend();


}

void Friend::flushFriend()
{
    QString name=client::GetInstance().Login_name;
    PDU* pdu=makePDU(0);
    memcpy(pdu->caData,name.toStdString().c_str(),32);
    pdu->uiMsgType=ENUM_MSG_TYPE_FLUSH_FRIEND_REQUIST;
    client::GetInstance().GetSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu=NULL;

}

void Friend::showflushFriend(QStringList userlist)
{
    qDebug()<<"展示出刷新好友界面";
    ui->listWidget->clear();
    ui->listWidget->addItems(userlist);
}

QListWidget *Friend::getFriend_LW()
{
    return ui->listWidget;
}

Friend::~Friend()
{
    delete m_pOnlineUser;
    delete m_pChat;
    delete ui;
}

void Friend::on_searchUser_PB_clicked()
{
    QString name=QInputDialog::getText(this,"搜索","用户名");
    if(name==client::GetInstance().Login_name){
        QMessageBox::information(this,"拒绝","无法查询自己");
        return;
    }
    PDU* pdu=makePDU(0);
    pdu->uiMsgType=ENUM_MSG_TYPE_SEARCH_USER_REQUIST;
    memcpy(pdu->caData,name.toStdString().c_str(),name.size());

    client::GetInstance().GetSocket().write((char*)pdu,pdu->uiPDULen);

    free(pdu);
    pdu=NULL;
}

void Friend::on_onlineUser_PB_clicked()
{
    if(m_pOnlineUser->isHidden()){
        m_pOnlineUser->show();
    }
    PDU* pdu=makePDU(0);
    pdu->uiMsgType=ENUM_MSG_TYPE_ONLINE_USER_REQUIST;
    client::GetInstance().GetSocket().write((char*)pdu,pdu->uiPDULen);

    free(pdu);
    pdu=NULL;

}

void Friend::on_flushFriend_PB_clicked()
{

    flushFriend();
}

void Friend::on_delFriend_PB_clicked()
{
    QListWidgetItem* Item= ui->listWidget->currentItem();
    if(Item==NULL){
        QMessageBox::information(this,"删除好友","请选择要删除的好友");
        return;
    }
    QString tarname=Item->text();
    int ret=QMessageBox::information(this,"删除好友",QString("是否删除好友'%1'").arg(tarname));
    if(ret==QMessageBox::No) return;
    PDU* pdu=makePDU(0);
    memcpy(pdu->caData,client::GetInstance().Login_name.toStdString().c_str(),32);
    memcpy(pdu->caData+32,tarname.toStdString().c_str(),32);
    pdu->uiMsgType=ENUM_MSG_TYPE_DEL_FRIEND_REQUIST;
    client::GetInstance().GetSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu=NULL;
}




void Friend::on_chat_PB_clicked()
{
    QListWidgetItem* item=ui->listWidget->currentItem();
    if(!item) {
        QMessageBox::information(this,"聊天","请选择想要聊天的好友");
        return;
    }
    if(m_pChat->isHidden()) m_pChat->show();
    m_pChat->m_strChatName=item->text();
}
