/********************************************************************************
** Form generated from reading UI file 'sharefile.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHAREFILE_H
#define UI_SHAREFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShareFile
{
public:
    QGridLayout *gridLayout;
    QListWidget *friend_LW;
    QVBoxLayout *verticalLayout;
    QPushButton *allSelect_PB;
    QPushButton *cancelAllSelect_PB;
    QSpacerItem *verticalSpacer;
    QPushButton *ok_PB;

    void setupUi(QWidget *ShareFile)
    {
        if (ShareFile->objectName().isEmpty())
            ShareFile->setObjectName(QString::fromUtf8("ShareFile"));
        ShareFile->resize(398, 276);
        gridLayout = new QGridLayout(ShareFile);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, -1, 0);
        friend_LW = new QListWidget(ShareFile);
        friend_LW->setObjectName(QString::fromUtf8("friend_LW"));
        friend_LW->setSelectionMode(QAbstractItemView::MultiSelection);

        gridLayout->addWidget(friend_LW, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        allSelect_PB = new QPushButton(ShareFile);
        allSelect_PB->setObjectName(QString::fromUtf8("allSelect_PB"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(14);
        allSelect_PB->setFont(font);

        verticalLayout->addWidget(allSelect_PB);

        cancelAllSelect_PB = new QPushButton(ShareFile);
        cancelAllSelect_PB->setObjectName(QString::fromUtf8("cancelAllSelect_PB"));
        cancelAllSelect_PB->setFont(font);

        verticalLayout->addWidget(cancelAllSelect_PB);

        verticalSpacer = new QSpacerItem(58, 118, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        ok_PB = new QPushButton(ShareFile);
        ok_PB->setObjectName(QString::fromUtf8("ok_PB"));
        ok_PB->setFont(font);

        verticalLayout->addWidget(ok_PB);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);


        retranslateUi(ShareFile);

        QMetaObject::connectSlotsByName(ShareFile);
    } // setupUi

    void retranslateUi(QWidget *ShareFile)
    {
        ShareFile->setWindowTitle(QCoreApplication::translate("ShareFile", "Form", nullptr));
        allSelect_PB->setText(QCoreApplication::translate("ShareFile", "\345\205\250\351\200\211", nullptr));
        cancelAllSelect_PB->setText(QCoreApplication::translate("ShareFile", "\345\217\226\346\266\210\345\205\250\351\200\211", nullptr));
        ok_PB->setText(QCoreApplication::translate("ShareFile", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShareFile: public Ui_ShareFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHAREFILE_H
