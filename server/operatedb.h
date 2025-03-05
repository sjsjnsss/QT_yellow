#ifndef OPERATEDB_H
#define OPERATEDB_H

#include <QObject>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QDebug>
#include<QSqlError>
#include<QSqlQuery>
class operateDB : public QObject
{
    Q_OBJECT
public:
   static operateDB& GetInstance();
   void connect();//和数据库建立连接
   bool handleRegist(const char* name,const char* pwd);//注册处理
   bool handleLogin(const char* name,const char* pwd);//登陆处理
   void handleOffcline(const char* name);//关闭用户在线功能
   int handleSearchUser(const char* name);//查询用户
   QStringList getOnlineUser() ;//获取在线用户
   int handleAddFriend(const char* curName,const char *tarName);//是否添加好友
   QStringList handleFlushFriend(const char* name);//刷新好友
   void handleAddFriendAgree(const char* curName,const char *tarName);//同意好友请求
   bool handleDelFriend(const char* curName,const char *tarName);//删除好友

    ~operateDB();
private:
   QSqlDatabase m_db;//创建数据库连接对象
   explicit operateDB(QObject *parent = nullptr);
   operateDB(const operateDB& Instance);
   operateDB& operator=(const operateDB&);
signals:

};



#endif // OPERATEDB_H
