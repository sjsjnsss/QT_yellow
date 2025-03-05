#ifndef FRIEND_H
#define FRIEND_H

#include <QWidget>
#include"onlineuser.h"
#include"chat.h"
namespace Ui {
class Friend;
}

class Friend : public QWidget
{
    Q_OBJECT

public:

    explicit Friend(QWidget *parent = nullptr);
    void flushFriend();
    void showflushFriend(QStringList userlist);
    QListWidget* getFriend_LW();
    OnlineUser* m_pOnlineUser;
    Chat* m_pChat;
    ~Friend();


private slots:
    void on_searchUser_PB_clicked();

    void on_onlineUser_PB_clicked();

    void on_flushFriend_PB_clicked();

    void on_delFriend_PB_clicked();

    void on_chat_PB_clicked();

private:
    Ui::Friend *ui;
};

#endif // FRIEND_H
