/********************************************************************************
** Form generated from reading UI file 'file.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILE_H
#define UI_FILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_File
{
public:
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *return_PB;
    QPushButton *mkDir_PB;
    QPushButton *rename_PB;
    QPushButton *delFile_PB;
    QPushButton *flushFile_PB;
    QPushButton *shareFile_PB;
    QPushButton *upload_PB;
    QPushButton *mvFile_PB;
    QPushButton *downloadFile_PB;
    QPushButton *delDir_PB;
    QListWidget *File_LW;

    void setupUi(QWidget *File)
    {
        if (File->objectName().isEmpty())
            File->setObjectName(QString::fromUtf8("File"));
        File->resize(422, 281);
        gridLayout_3 = new QGridLayout(File);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 9, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        return_PB = new QPushButton(File);
        return_PB->setObjectName(QString::fromUtf8("return_PB"));

        gridLayout->addWidget(return_PB, 0, 1, 1, 1);

        mkDir_PB = new QPushButton(File);
        mkDir_PB->setObjectName(QString::fromUtf8("mkDir_PB"));

        gridLayout->addWidget(mkDir_PB, 1, 0, 1, 1);

        rename_PB = new QPushButton(File);
        rename_PB->setObjectName(QString::fromUtf8("rename_PB"));

        gridLayout->addWidget(rename_PB, 1, 1, 1, 1);

        delFile_PB = new QPushButton(File);
        delFile_PB->setObjectName(QString::fromUtf8("delFile_PB"));

        gridLayout->addWidget(delFile_PB, 3, 0, 1, 1);

        flushFile_PB = new QPushButton(File);
        flushFile_PB->setObjectName(QString::fromUtf8("flushFile_PB"));

        gridLayout->addWidget(flushFile_PB, 0, 0, 1, 1);

        shareFile_PB = new QPushButton(File);
        shareFile_PB->setObjectName(QString::fromUtf8("shareFile_PB"));

        gridLayout->addWidget(shareFile_PB, 2, 1, 1, 1);

        upload_PB = new QPushButton(File);
        upload_PB->setObjectName(QString::fromUtf8("upload_PB"));

        gridLayout->addWidget(upload_PB, 3, 1, 1, 1);

        mvFile_PB = new QPushButton(File);
        mvFile_PB->setObjectName(QString::fromUtf8("mvFile_PB"));

        gridLayout->addWidget(mvFile_PB, 4, 0, 1, 1);

        downloadFile_PB = new QPushButton(File);
        downloadFile_PB->setObjectName(QString::fromUtf8("downloadFile_PB"));

        gridLayout->addWidget(downloadFile_PB, 4, 1, 1, 1);

        delDir_PB = new QPushButton(File);
        delDir_PB->setObjectName(QString::fromUtf8("delDir_PB"));

        gridLayout->addWidget(delDir_PB, 2, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 1, 1, 1);

        File_LW = new QListWidget(File);
        File_LW->setObjectName(QString::fromUtf8("File_LW"));
        File_LW->setFrameShape(QFrame::NoFrame);

        gridLayout_2->addWidget(File_LW, 0, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(File);

        QMetaObject::connectSlotsByName(File);
    } // setupUi

    void retranslateUi(QWidget *File)
    {
        File->setWindowTitle(QCoreApplication::translate("File", "\346\226\207\344\273\266", nullptr));
        return_PB->setText(QCoreApplication::translate("File", "\350\277\224\345\233\236\344\270\212\344\270\200\347\272\247", nullptr));
        mkDir_PB->setText(QCoreApplication::translate("File", "\345\210\233\345\273\272\346\226\207\344\273\266\345\244\271", nullptr));
        rename_PB->setText(QCoreApplication::translate("File", "\351\207\215\345\221\275\345\220\215", nullptr));
        delFile_PB->setText(QCoreApplication::translate("File", "\345\210\240\351\231\244\346\226\207\344\273\266", nullptr));
        flushFile_PB->setText(QCoreApplication::translate("File", "\345\210\267\346\226\260\346\226\207\344\273\266", nullptr));
        shareFile_PB->setText(QCoreApplication::translate("File", "\345\210\206\344\272\253\346\226\207\344\273\266", nullptr));
        upload_PB->setText(QCoreApplication::translate("File", "\344\270\212\344\274\240\346\226\207\344\273\266", nullptr));
        mvFile_PB->setText(QCoreApplication::translate("File", "\347\247\273\345\212\250\346\226\207\344\273\266", nullptr));
        downloadFile_PB->setText(QCoreApplication::translate("File", "\344\270\213\350\275\275\346\226\207\344\273\266", nullptr));
        delDir_PB->setText(QCoreApplication::translate("File", "\345\210\240\351\231\244\346\226\207\344\273\266\345\244\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class File: public Ui_File {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILE_H
