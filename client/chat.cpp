#include "chat.h"
#include "ui_chat.h"
#include"protocol.h"
#include"client.h"
Chat::Chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
}

void Chat::updateShow_TE(QString chatMsg)
{
    ui->show_TE->append(chatMsg);
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_ssend_PB_clicked()
{
    QString ChatMsg=ui->input_LE->text();
    if(ChatMsg.isEmpty()){
        return;
    }
    PDU* pdu=makePDU(ChatMsg.size()+1);
    memcpy(pdu->caData,client::GetInstance().Login_name.toStdString().c_str(),32);
    memcpy(pdu->caData+32,m_strChatName.toStdString().c_str(),32);
    memcpy(pdu->caMsg,ChatMsg.toStdString().c_str(),sizeof(ChatMsg));
    pdu->uiMsgType=ENUM_MSG_TYPE_CHAT_REQUIST;

    client::GetInstance().GetSocket().write((char*)pdu,pdu->uiPDULen);
    qDebug()<<"两个用户"<<pdu->caData<<"and"<<pdu->caData+32<<"消息内容"<<pdu->caMsg<<"协议类型:"<<pdu->uiMsgType;
    free(pdu);
    pdu=NULL;
}
