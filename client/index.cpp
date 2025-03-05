#include "index.h"
#include "ui_index.h"

Index::Index(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Index)
{
    ui->setupUi(this);
}

Index &Index::GetInstance()
{
    static Index Instance;
    return Instance;
}

Friend *Index::getFriend()
{
    return ui->friend_page;
}

File *Index::getFile()
{
    return ui->file_page;
}

Index::~Index()
{
    delete ui;
}


void Index::on_friend_PB_clicked()
{
        ui->stackedWidget->setCurrentIndex(0);
//        ui->file_PB->setStyleSheet("QPushButtton{border:none;padding:20;}");
//        ui->friend_PB->setStyleSheet("QPushButtton{border:none;background-color: rgb(255, 255, 255);padding:20;}");
}

void Index::on_file_PB_clicked()
{
       ui->stackedWidget->setCurrentIndex(1);
//       ui->friend_PB->setStyleSheet("QPushButtton{border:none;padding:20;}");
//       ui->file_PB->setStyleSheet("QPushButtton{border:none;background-color: rgb(255, 255, 255);padding:20;}");
}
