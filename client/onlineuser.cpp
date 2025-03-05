#include "onlineuser.h"
#include "ui_onlineuser.h"
#include"client.h"


OnlineUser::OnlineUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OnlineUser)
{
    ui->setupUi(this);
}

OnlineUser::~OnlineUser()
{
    delete ui;
}

void OnlineUser::showOnlineUser(QStringList userlist)
{
    ui->listWidget->clear();
    ui->listWidget->addItems(userlist);
}

void OnlineUser::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{

    QString strCurName = client::GetInstance().Login_name;
    QString strTarName=item->text();
    PDU* pdu=makePDU(0);
    pdu->uiMsgType=ENUM_MSG_TYPE_ADD_FRIEND_REQUIST;
    memcpy(pdu->caData,strCurName.toStdString().c_str(),32);
    memcpy(pdu->caData+32,strTarName.toStdString().c_str(),32);
    client::GetInstance().GetSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu=NULL;
}
