#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include<QFile>
#include<QMessageBox>
#include<QDebug>
#include<QHostAddress>
#include"mytcpserver.h"
QT_BEGIN_NAMESPACE
namespace Ui { class server; }
QT_END_NAMESPACE

class server : public QWidget
{
    Q_OBJECT

public:
    QString m_filerootPath;
    void loadconfig();
    server(QWidget *parent = nullptr);
    static server& GetInstance();
    ~server();

private:

    server(const server& Instance);
    server& operator=(const server&);
    Ui::server *ui;
    QString m_strIP;
    quint16 m_usport;
};
#endif // SERVER_H
