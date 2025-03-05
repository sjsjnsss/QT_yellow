#ifndef MSGHANDLE_H
#define MSGHANDLE_H
#include<QString>
#include<QFile>
#include"protocol.h"

class MsgHandle
{
public:
    MsgHandle();
    PDU* regist(PDU* pdu);
    PDU* login(PDU* pdu,QString& m_name);
    PDU* searchUser(PDU* pdu);
    PDU* onlineUser();
    PDU* addFriend(PDU* pdu);
    PDU* addFriendAgree(PDU* pdu);
    void addFriendRefuse(PDU* pdu);
    PDU* flushFriend(PDU* pdu);
    PDU* delFriend(PDU* pdu);
    PDU* mkdir(PDU* pdu);
    void chat(PDU* pdu);
    PDU* flushFile(PDU* pdu);
    PDU* delDir(PDU* pdu);
    PDU* delFile(PDU* pdu);
    PDU* renameFile(PDU* pdu);
    PDU* mvFile(PDU* pdu);
    PDU* uploadFile(PDU* pdu);
    PDU* uploadFileData(PDU* pdu);
    PDU* shareFile(PDU* pdu);
    PDU* shareFileAgree(PDU* pdu);
    bool copyDir(QString strSourcePath,QString strTargetPath);

private:
    qint64 m_iUploadTotal;
    qint64 m_iUploadReceived;
    QFile m_fUploadFile;
    bool m_bUpload;

};

#endif // MSGHANDLE_H
