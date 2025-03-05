#include "file.h"
#include "ui_file.h"
#include"client.h"
#include<QInputDialog>
#include<QFileDialog>
File::File(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::File)
{
    ui->setupUi(this);
    m_strcurpath=QString("%1/%2").arg(client::GetInstance().m_filerootPath).arg(client::GetInstance().Login_name);
    m_struserpath=m_strcurpath;
    bUpload=false;
    sharefile=new ShareFile;
    flushFile();
}

File::~File()
{
    delete ui;
}

void File::flushFile()
{
    PDU* pdu=makePDU(m_strcurpath.size()+1);
    memcpy(pdu->caMsg,m_strcurpath.toStdString().c_str(),m_strcurpath.size());
    pdu->uiMsgType=ENUM_MSG_TYPE_FLUSH_FILE_REQUIST;
    client::GetInstance().GetSocket().write((char*)pdu,pdu->uiPDULen);
}

void File::updateFile(QList<FileInfo *> pFileList)
{
    foreach(FileInfo* pFileInfo,m_pFileInfoList){
        delete pFileInfo;
    }
    m_pFileInfoList=pFileList;
    ui->File_LW->clear();
    foreach(FileInfo* pFileInfo,pFileList){
        QListWidgetItem* pItem=new QListWidgetItem;
        qDebug()<<"客户端接收到的文件类型"<<pFileInfo->iFileType;
        if(pFileInfo->iFileType==0){
            pItem->setIcon(QIcon(QPixmap(":/dir.png")));
        }
        if(pFileInfo->iFileType==1){
            pItem->setIcon(QIcon(QPixmap(":/file.png")));
        }
        pItem->setText(pFileInfo->caName);
        ui->File_LW->addItem(pItem);
    }


}

void File::uploadFile()
{
    //打开文件,构建PDU,循环读取文件,将文件内容放进caMsg,发送pdu,关闭文件
    QFile file(strUploadFilePath);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,"打开文件","打开文件失败");
    }
    bUpload=1;
    qint64 ret=0;
    PDU* datapdu=makePDU(4096);
    datapdu->uiMsgType=ENUM_MSG_TYPE_UP_FILE_DATA_REQUIST;
    while(true){
        ret=file.read(datapdu->caMsg,4096);
        if(ret==0){
            break;
        }
        if(ret<0){
            QMessageBox::warning(this,"上传文件","上传文件失败");
            break;
        }
        datapdu->uiMsgLen=ret;
        datapdu->uiPDULen=ret+sizeof(PDU);
        client::GetInstance().GetSocket().write((char*)datapdu,datapdu->uiPDULen);
    }
    bUpload=0;
    file.close();
    free(datapdu);
    datapdu=NULL;
}

void File::on_mkDir_PB_clicked()
{

    QString strNewDir= QInputDialog::getText(this,"新建文件夹","新建文件夹名");
    if(strNewDir.isEmpty()||strNewDir.size()>32){
        QMessageBox::warning(this,"警告","文件名非法");
        return;
    }
    PDU* pdu=makePDU(m_struserpath.size()+1);
    pdu->uiMsgType=ENUM_MSG_TYPE_MKDIR_REQUIST;
    memcpy(pdu->caData,strNewDir.toStdString().c_str(),strNewDir.size());
    memcpy(pdu->caMsg,m_struserpath.toStdString().c_str(),m_struserpath.size());
    client::GetInstance().GetSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu=NULL;
}

void File::on_flushFile_PB_clicked()
{
    flushFile();
}

void File::on_delDir_PB_clicked()
{
    QListWidgetItem* pItem=ui->File_LW->currentItem();
    if(pItem==NULL){
        QMessageBox::warning(this,"删除文件夹","请选择文件夹");
    }
    QString DelDirName=pItem->text();
    foreach(FileInfo* pFileInfo,m_pFileInfoList){
        if(DelDirName==pFileInfo->caName&&pFileInfo->iFileType==1){
            QMessageBox::warning(this,"删除文件夹","选择的不是文件夹");
            return;
        }
    }
    int ret=QMessageBox::question(this,"删除文件夹",QString("是否确认删除文件夹 '%1'").arg(DelDirName));
    if(ret==QMessageBox::No) return;
    QString FilePath=QString("%1/%2").arg(m_strcurpath).arg(DelDirName);
    PDU* pdu=makePDU(FilePath.size()+1);
    pdu->uiMsgType=ENUM_MSG_TYPE_DELDIR_REQUIST;
    memcpy(pdu->caMsg,FilePath.toStdString().c_str(),FilePath.size());
    client::GetInstance().GetSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu=NULL;
}


void File::on_delFile_PB_clicked()
{
    QListWidgetItem* pItem=ui->File_LW->currentItem();
    if(pItem==NULL){
        QMessageBox::warning(this,"删除文件","请选择文件");
    }
    QString DelFileName=pItem->text();
    foreach(FileInfo* pFileInfo,m_pFileInfoList){
        if(DelFileName==pFileInfo->caName&&pFileInfo->iFileType==0){
            QMessageBox::warning(this,"删除文件","选择的不是文件");
            return;
        }
    }
    int ret=QMessageBox::question(this,"删除文件",QString("是否确认删除文件 '%1'").arg(DelFileName));
    if(ret==QMessageBox::No) return;
    QString FilePath=QString("%1/%2").arg(m_strcurpath).arg(DelFileName);
    PDU* pdu=makePDU(FilePath.size()+1);
    pdu->uiMsgType=ENUM_MSG_TYPE_DELFILE_REQUIST;
    memcpy(pdu->caMsg,FilePath.toStdString().c_str(),FilePath.size());
    client::GetInstance().GetSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu=NULL;
}

void File::on_rename_PB_clicked()
{
    QListWidgetItem* pItem=ui->File_LW->currentItem();
    if(pItem==NULL){
        QMessageBox::warning(this,"重复名文件","请选择要重复名的文件");
        return;
    }
    QString newFileName=QInputDialog::getText(this,"文件重命名","输入新的文件名");
    if(newFileName.isEmpty()||newFileName.size()>32){
        QMessageBox::warning(this,"重复名失败","文件名非法");
        return;
    }

    PDU* pdu=makePDU(m_strcurpath.size()+1);
    memcpy(pdu->caData,newFileName.toStdString().c_str(),32);
    memcpy(pdu->caData+32,pItem->text().toStdString().c_str(),32);
    memcpy(pdu->caMsg,m_strcurpath.toStdString().c_str(),m_strcurpath.size());
    pdu->uiMsgType=ENUM_MSG_TYPE_RENAME_FILE_REQUIST;
    client::GetInstance().GetSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu=NULL;
}

void File::on_File_LW_itemDoubleClicked(QListWidgetItem *item)
{
    QString DirName=item->text();
    foreach(FileInfo* pFileInfo,m_pFileInfoList){
        if(DirName==pFileInfo->caName&&pFileInfo->iFileType==1){
            return;
        }
    }
    m_strcurpath=QString("%1/%2").arg(m_strcurpath).arg(DirName);
    Index::GetInstance().getFile()->flushFile();
}

void File::on_return_PB_clicked()
{
    if(m_strcurpath==m_struserpath){
        QMessageBox::warning(this,"返回上一级","已返回至顶层目录");
        return;
    }
    int index=m_strcurpath.lastIndexOf('/');
    m_strcurpath.remove(index,m_strcurpath.size()-index);
    Index::GetInstance().getFile()->flushFile();

}


void File::on_mvFile_PB_clicked()
{
    //移动文件 按钮处理
    if(ui->mvFile_PB->text()=="移动文件"){
        QListWidgetItem* pItem=ui->File_LW->currentItem();
        if(pItem==NULL){
            QMessageBox::warning(this,"移动文件","请选择想要移动的文件");
            return;
        }
        mvFileName=pItem->text();
        mvFilepath=m_strcurpath+'/'+mvFileName;
        QMessageBox::information(this,"移动文件","请选择想要移动到的目录");
        ui->mvFile_PB->setText("确定/取消");
        return;
    }
    //确认/取消 按钮处理
    QListWidgetItem* pItem=ui->File_LW->currentItem();
    QString DirName=pItem?pItem->text():"\0";
    QString tarPath;
    QString mesMsg;
    if(pItem==NULL){//用户没有选择目录,默认移动到当前目录
        tarPath=m_strcurpath+'/'+mvFileName;
        mesMsg="是否移动到当前文件夹";
    }else{
        foreach(FileInfo* pFileInfo,m_pFileInfoList){
            if(pFileInfo->caName==DirName&&pFileInfo->iFileType!=0){
                QMessageBox::warning(this,"移动文件","选中的不是文件夹");
                return;
            }
        }
        tarPath=m_strcurpath+'/'+DirName+'/'+mvFileName;
        mesMsg=QString("是否移动到文件夹 %1").arg(DirName);
    }
    qDebug()<<"srcPath:"<<mvFilepath<<"tarpath"<<tarPath;
    int ret=QMessageBox::question(this,"移动文件",mesMsg,"确定","取消");
    ui->mvFile_PB->setText("移动文件");
    if(ret!=0) return;
    //源路径和目标路径放在camsg中将两个长度放在cadata中
    int srcLen=mvFilepath.size();
    int tarLen=tarPath.size();
    PDU* pdu=makePDU(srcLen+tarLen+1);
    memcpy(pdu->caData,&srcLen,sizeof(int));
    memcpy(pdu->caData+sizeof(int),&tarLen,sizeof(int));
    memcpy(pdu->caMsg,mvFilepath.toStdString().c_str(),srcLen);
    memcpy(pdu->caMsg+srcLen+1,tarPath.toStdString().c_str(),tarLen);
    pdu->uiMsgType=ENUM_MSG_TYPE_MOVE_FILE_REQUIST;
    client::GetInstance().GetSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu=NULL;
}



void File::on_upload_PB_clicked()
{
    //判断文件是否已上传
    if(bUpload==1){
        QMessageBox::warning(this,"上传失败","有文件正在上传");
        return;
    }
    //文件弹窗获得上传路径
    strUploadFilePath= QFileDialog::getOpenFileName();//获取文件真实地址
    if(strUploadFilePath.isEmpty()){
        QMessageBox::warning(this,"上传失败","请选择要上传的文件");
        return;
    }
    //从路径获取文件名和文件大小
    int index=strUploadFilePath.lastIndexOf('/');
    QString strFileName=strUploadFilePath.right(strUploadFilePath.size()-index-1);
    QFile file(strUploadFilePath);
    qint64 filesize=file.size();
    PDU* pdu=makePDU(m_strcurpath.size()+1);
    pdu->uiMsgType=ENUM_MSG_TYPE_UP_FILE_REQUIST;
    //文件名和大小放进cadata中,路径放进camsg中
    memcpy(pdu->caData,strFileName.toStdString().c_str(),32);
    memcpy(pdu->caData+32,&filesize,sizeof(qint64));
    memcpy(pdu->caMsg,m_strcurpath.toStdString().c_str(),m_strcurpath.size());
    client::GetInstance().GetSocket().write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu=NULL;
}

void File::on_shareFile_PB_clicked()
{
    QListWidgetItem* pItem=ui->File_LW->currentItem();
    if(pItem==NULL){
        QMessageBox::warning(this,"分享文件","请选择要分享的文件");
        return;
    }
    shareFileName=pItem->text();
    sharefile->updateFriend_LW();
    if(sharefile->isHidden()){
       sharefile->show();
    }

}
