#ifndef FILE_H
#define FILE_H

#include <QWidget>
#include<QListWidgetItem>
#include"protocol.h"
#include"sharefile.h"
namespace Ui {
class File;
}

class File : public QWidget
{
    Q_OBJECT

public:
    explicit File(QWidget *parent = nullptr);
    ~File();
    QString m_strcurpath;
    QString m_struserpath;
    QList<FileInfo*> m_pFileInfoList;
    void flushFile();
    void updateFile(QList<FileInfo*> pFileList);
    void uploadFile();
    QString mvFilepath;
    QString mvFileName;
    QString strUploadFilePath;
    bool bUpload;
    ShareFile* sharefile;
    QString shareFileName;
private slots:
    void on_mkDir_PB_clicked();

    void on_flushFile_PB_clicked();

    void on_delDir_PB_clicked();

    void on_delFile_PB_clicked();

    void on_rename_PB_clicked();

    void on_File_LW_itemDoubleClicked(QListWidgetItem *item);

    void on_return_PB_clicked();

    void on_mvFile_PB_clicked();

    void on_upload_PB_clicked();

    void on_shareFile_PB_clicked();

private:
    Ui::File *ui;
};

#endif // FILE_H
