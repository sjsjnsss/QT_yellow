#include"protocol.h"
#include<stdlib.h>

PDU* makePDU(uint uiMsgLen){

    uint uiPDULen=uiMsgLen+sizeof(PDU);
    PDU* pdu=(PDU*)malloc(uiPDULen);
    if(pdu==NULL){
        exit(1);
    }
    memset(pdu,0,uiPDULen);
    pdu->uiMsgLen=uiMsgLen;
    pdu->uiPDULen=uiPDULen;
    return pdu;

}
