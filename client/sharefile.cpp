#include "sharefile.h"
#include "ui_sharefile.h"
#include"client.h"
#include"protocol.h"
#include<index.h>
ShareFile::ShareFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShareFile)
{
    ui->setupUi(this);
}

ShareFile::~ShareFile()
{
    delete ui;
}

void ShareFile::updateFriend_LW()
{
    ui->friend_LW->clear();
    QListWidget* friend_LW=Index::GetInstance().getFriend()->getFriend_LW();
    for(int i=0;i<friend_LW->count();i++){
        QListWidgetItem* friendItem=friend_LW->item(i);
        QListWidgetItem* newItem=new QListWidgetItem(*friendItem);
        ui->friend_LW->addItem(newItem);
    }
}

void ShareFile::on_allSelect_PB_clicked()
{
    for(int i=0;i<ui->friend_LW->count();i++){
        ui->friend_LW->item(i)->setSelected(true);
    }
}

void ShareFile::on_cancelAllSelect_PB_clicked()
{

    for(int i=0;i<ui->friend_LW->count();i++){
        ui->friend_LW->item(i)->setSelected(false);
    }
}

void ShareFile::on_ok_PB_clicked()
{
    QString strCurPath=Index::GetInstance().getFile()->m_strcurpath;
    QString strFileName=Index::GetInstance().getFile()->shareFileName;
    QString strPath=QString("%1/%2").arg(strCurPath).arg(strFileName);
    QString curname=client::GetInstance().Login_name;
    QList<QListWidgetItem*> pItems= ui->friend_LW->selectedItems();
    int friendCount=pItems.size();
    //选择的好友名和路径放入camsg,当前用户名和选中的好友数量放入caData
    PDU* pdu=makePDU(friendCount*32+strPath.size()+1);
    pdu->uiMsgType=ENUM_MSG_TYPE_SHARE_FILE_REQUIST;
    memcpy(pdu->caData,curname.toStdString().c_str(),32);
    memcpy(pdu->caData+32,&friendCount,sizeof(int));
    for(int i=0;i<friendCount;i++){
        memcpy((char*)(pdu->caMsg)+i*32,pItems.at(i)->text().toStdString().c_str(),32);
    }
    memcpy((char*)(pdu->caMsg)+friendCount*32,strPath.toStdString().c_str(),strPath.size());
    client::GetInstance().GetSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu=NULL;
}









