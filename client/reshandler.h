#ifndef RESHANDLER_H
#define RESHANDLER_H
#include"protocol.h"

class resHandler
{
public:
    resHandler();
    void regist(PDU* pdu);
    void login(PDU* pdu);
    void searchUser(PDU* pdu);
    void onlineUser(PDU* pdu);
    void addFriend(PDU* pdu);//当前客户端提示框
    void addFriendRequest(PDU* pdu);//目标客户端提示框
    void addFriendAgree();
    void addFriendRefuse(PDU* pdu);
    void flushFriend(PDU* pdu);
    void delFriend(PDU* pdu);
    void chat(PDU* pdu);
    void mkdir(PDU* pdu);
    void flushFile(PDU* pdu);
    void delDir(PDU* pdu);
    void delFile(PDU* pdu);
    void renameFile(PDU* pdu);
    void moveFile(PDU* pdu);
    void uploadFile(PDU* pdu);
    void uploadFileData(PDU* pdu);
    void shareFile(PDU* pdu);
    void shareFileRequest(PDU* pdu);
    void shareFileAgree(PDU* pdu);

};

#endif // RESHANDLER_H
