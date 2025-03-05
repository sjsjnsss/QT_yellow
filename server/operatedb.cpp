#include "operatedb.h"

operateDB::operateDB(QObject *parent) : QObject(parent)
{
    m_db=QSqlDatabase::addDatabase("QMYSQL");//初始化对象
}




operateDB& operateDB::GetInstance()
{
    static operateDB Instance;
    return Instance;
}

bool operateDB::handleRegist(const char* name,const char* pwd)
{
    if(name==NULL||pwd==NULL){
        return false;
    }
    QString sql=QString("select * from user_info where name='%1'").arg(name);
    QSqlQuery q;
    if(q.exec(sql)&&q.next()){//如果执行成功并且有数据
        return false;
    }
    sql=QString("insert into user_info(name,pwd)values('%1','%2');").arg(name).arg(pwd);
    return q.exec(sql);


}

bool operateDB::handleLogin(const char *name, const char *pwd)
{
    if(name==NULL||pwd==NULL){
        return false;
    }
    QString sql=QString("select * from user_info where name='%1' and pwd='%2'").arg(name).arg(pwd);
    QSqlQuery q;
    if(q.exec(sql)&&q.next()){
        QString set=QString("update user_info set online=1 where name='%1'").arg(name);
        q.exec(set);
        return q.exec(set);
    }
    else return false;

}

void operateDB::handleOffcline(const char *name)
{
    if(name==NULL){
        qDebug()<<"handleOffline name is NULL";
        return;

    }
    QString sql=QString("update user_info set online=0 where name='%1'").arg(name);
    QSqlQuery q;
    q.exec(sql);
}

int operateDB::handleSearchUser(const char *name)
{
    //-1:用户不存在 0:用户不在线 1:用户在线
    if(name==NULL){
        qDebug()<<"handleSearchUser name is NULL";
        return -1;

    }
    QString sql=QString("select online from user_info where name='%1'").arg(name);
    QSqlQuery q;
    q.exec(sql);
    if(q.next()){
        qDebug()<<"ret返回值"<<q.value(0).toInt();
        return q.value(0).toInt();
    }
    return -1;
}

QStringList operateDB::getOnlineUser()
{
    QStringList res;
    QString sql=QString("select name from user_info where online=1");
    QSqlQuery q;
    q.exec(sql);
    res.clear();
    while(q.next()){
        res.append(q.value(0).toString());
    }
    return res;
}

int operateDB::handleAddFriend(const char *curName, const char *tarName)
{//-1:报错  -2:已经是好友 1:在线 0:不在线
    if(curName==NULL||tarName==NULL) return -1;
    QString sql=QString(R"(
       select * from friend where (
       user_id=(select id from user_info where name='%1')
        and
       friend_id=(select id from user_info where name='%2')
       )
        or(
       friend_id=(select id from user_info where name='%3')
       and
       user_id=(select id from user_info where name='%4')
       );
        )").arg(curName).arg(tarName).arg(curName).arg(tarName);
    QSqlQuery q;
    q.exec(sql);
    if(q.next()) return -2;
    sql=QString("select online from user_info where name='%1'").arg(tarName);
    q.exec(sql);
    if(q.next()){
        return q.value(0).toInt();
    }
    return -1;

}

QStringList operateDB::handleFlushFriend(const char *name)
{
    QStringList res;
    QString sql=QString(R"(
       select name from user_info where
       online=1 and
       id in (select user_id from friend where friend_id=(select id from user_info where name='%1')
               union
              select friend_id from friend where user_id=(select id from user_info where name='%1')
        );
        )").arg(name);
    QSqlQuery q;
    q.exec(sql);
    res.clear();
    while(q.next()){
        res.append(q.value(0).toString());
    }
    return res;
}

void operateDB::handleAddFriendAgree(const char *curName, const char *tarName)
{
    if(curName==NULL||tarName==NULL) return;
    QString sql=QString(R"(
     insert into friend(user_id,friend_id)
     (select u1.ID,u2.ID from user_info u1,user_info u2 where u1.name='%1' and u2.name='%2');
     )").arg(curName).arg(tarName);
    QSqlQuery q;
    q.exec(sql);
}

bool operateDB::handleDelFriend(const char *curName, const char *tarName)
{
    qDebug()<<"操作库函数接收两个用户名:"<<curName<<"and"<<tarName;
    if(curName==NULL||tarName==NULL) return 0;
    QString usesql=QString(R"( select * from friend where (
      user_id=(select id from user_info where name='%1')
       and
      friend_id=(select id from user_info where name='%2')
      )
       or(
      friend_id=(select id from user_info where name='%3')
      and
      user_id=(select id from user_info where name='%4')
      );
       )").arg(curName).arg(tarName).arg(curName).arg(tarName);

    QSqlQuery q;
    q.exec(usesql);

    if(!q.next()) return 0;

    QString sql=QString(R"( delete from friend where (
     user_id=(select id from user_info where name='%1')
      and
     friend_id=(select id from user_info where name='%2')
     )
      or(
     friend_id=(select id from user_info where name='%3')
     and
     user_id=(select id from user_info where name='%4')
     );
      )").arg(curName).arg(tarName).arg(curName).arg(tarName);

    q.exec(sql);

    return 1;
}

void operateDB::connect()
{
    m_db.setHostName("localhost");
    m_db.setPort(3306);
    m_db.setUserName("root");
    m_db.setPassword("123456");
    m_db.setDatabaseName("netdisk");
    if(!m_db.open()){
        QMessageBox::critical(0,"连接数据库失败",m_db.lastError().text());
    }
    else qDebug()<<"数据库连接成功";
}

operateDB::~operateDB()
{
    m_db.close();
}


