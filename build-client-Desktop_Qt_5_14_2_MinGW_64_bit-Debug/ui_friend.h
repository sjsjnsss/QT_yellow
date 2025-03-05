/********************************************************************************
** Form generated from reading UI file 'friend.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIEND_H
#define UI_FRIEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Friend
{
public:
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QListWidget *listWidget;
    QGridLayout *gridLayout;
    QPushButton *chat_PB;
    QPushButton *flushFriend_PB;
    QPushButton *delFriend_PB;
    QSpacerItem *verticalSpacer;
    QPushButton *searchUser_PB;
    QPushButton *onlineUser_PB;

    void setupUi(QWidget *Friend)
    {
        if (Friend->objectName().isEmpty())
            Friend->setObjectName(QString::fromUtf8("Friend"));
        Friend->resize(354, 268);
        gridLayout_3 = new QGridLayout(Friend);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setVerticalSpacing(0);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        listWidget = new QListWidget(Friend);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setFrameShape(QFrame::NoFrame);

        gridLayout_2->addWidget(listWidget, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        chat_PB = new QPushButton(Friend);
        chat_PB->setObjectName(QString::fromUtf8("chat_PB"));

        gridLayout->addWidget(chat_PB, 0, 0, 1, 1);

        flushFriend_PB = new QPushButton(Friend);
        flushFriend_PB->setObjectName(QString::fromUtf8("flushFriend_PB"));

        gridLayout->addWidget(flushFriend_PB, 1, 0, 1, 1);

        delFriend_PB = new QPushButton(Friend);
        delFriend_PB->setObjectName(QString::fromUtf8("delFriend_PB"));

        gridLayout->addWidget(delFriend_PB, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);

        searchUser_PB = new QPushButton(Friend);
        searchUser_PB->setObjectName(QString::fromUtf8("searchUser_PB"));

        gridLayout->addWidget(searchUser_PB, 4, 0, 1, 1);

        onlineUser_PB = new QPushButton(Friend);
        onlineUser_PB->setObjectName(QString::fromUtf8("onlineUser_PB"));

        gridLayout->addWidget(onlineUser_PB, 5, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(Friend);

        QMetaObject::connectSlotsByName(Friend);
    } // setupUi

    void retranslateUi(QWidget *Friend)
    {
        Friend->setWindowTitle(QCoreApplication::translate("Friend", "\346\234\213\345\217\213", nullptr));
        chat_PB->setText(QCoreApplication::translate("Friend", "\350\201\212   \345\244\251", nullptr));
        flushFriend_PB->setText(QCoreApplication::translate("Friend", "\345\210\267\346\226\260\345\245\275\345\217\213", nullptr));
        delFriend_PB->setText(QCoreApplication::translate("Friend", "\345\210\240\351\231\244\345\245\275\345\217\213", nullptr));
        searchUser_PB->setText(QCoreApplication::translate("Friend", "\346\237\245\346\211\276\347\224\250\346\210\267", nullptr));
        onlineUser_PB->setText(QCoreApplication::translate("Friend", "\345\234\250\347\272\277\347\224\250\346\210\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Friend: public Ui_Friend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIEND_H
