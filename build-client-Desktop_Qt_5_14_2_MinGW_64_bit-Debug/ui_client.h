/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_client
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *user_label;
    QLineEdit *user_LE;
    QLabel *pwd_label;
    QLineEdit *pwd_LE;
    QPushButton *regist_PB;
    QSpacerItem *horizontalSpacer;
    QPushButton *login_PB;

    void setupUi(QMainWindow *client)
    {
        if (client->objectName().isEmpty())
            client->setObjectName(QString::fromUtf8("client"));
        client->resize(293, 191);
        centralwidget = new QWidget(client);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        user_label = new QLabel(centralwidget);
        user_label->setObjectName(QString::fromUtf8("user_label"));

        gridLayout->addWidget(user_label, 0, 0, 1, 1);

        user_LE = new QLineEdit(centralwidget);
        user_LE->setObjectName(QString::fromUtf8("user_LE"));

        gridLayout->addWidget(user_LE, 0, 1, 1, 3);

        pwd_label = new QLabel(centralwidget);
        pwd_label->setObjectName(QString::fromUtf8("pwd_label"));

        gridLayout->addWidget(pwd_label, 1, 0, 1, 1);

        pwd_LE = new QLineEdit(centralwidget);
        pwd_LE->setObjectName(QString::fromUtf8("pwd_LE"));
        pwd_LE->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(pwd_LE, 1, 1, 1, 3);

        regist_PB = new QPushButton(centralwidget);
        regist_PB->setObjectName(QString::fromUtf8("regist_PB"));

        gridLayout->addWidget(regist_PB, 2, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 2, 1, 1);

        login_PB = new QPushButton(centralwidget);
        login_PB->setObjectName(QString::fromUtf8("login_PB"));

        gridLayout->addWidget(login_PB, 2, 3, 1, 1);

        client->setCentralWidget(centralwidget);

        retranslateUi(client);

        QMetaObject::connectSlotsByName(client);
    } // setupUi

    void retranslateUi(QMainWindow *client)
    {
        client->setWindowTitle(QCoreApplication::translate("client", "\345\256\242\346\210\267\347\253\257", nullptr));
        user_label->setText(QCoreApplication::translate("client", "\347\224\250\346\210\267\345\220\215:", nullptr));
        pwd_label->setText(QCoreApplication::translate("client", "\345\257\206\347\240\201:", nullptr));
        regist_PB->setText(QCoreApplication::translate("client", "\346\263\250\345\206\214", nullptr));
        login_PB->setText(QCoreApplication::translate("client", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class client: public Ui_client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
