#include "to_register.h"
#include "ui_to_register.h"
#include <iostream>
#include <fstream>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QMessageBox>
#include <string>
#include <map>
#define filename "userinfo.txt"
using namespace std;
extern int music_flag;


extern map<QString,QString> mp;

QString register_username;
QString register_password;


to_register::to_register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::to_register)
{
    ui->setupUi(this);
    if(music_flag==1){
        ui->play_music->show();
        ui->stop_music->hide();
    }else{
        ui->play_music->hide();
        ui->stop_music->show();
    }
}

to_register::~to_register()
{
    delete ui;
}

void to_register::receive_show(){
    if(music_flag==1){
        ui->play_music->show();
        ui->stop_music->hide();
    }else{
        ui->play_music->hide();
        ui->stop_music->show();
    }
    this->show();
}

void to_register::register_account(){
    // 打开文件 设定追加模式
    QFile file(filename);
    //    file.open(QIODevice::Append|QIODevice::Text);
    file.open(QIODevice::Append|QIODevice::Text);
    QTextStream textstr(&file);
    // 先把现在文件的内容都读出来 看看用户名是否已经被用过
    read_test();


    if(mp[register_username]!=""){
        QMessageBox::about(this,"注册失败","用户名已存在");
        return;
    }else if(register_username.size()<4){
        QMessageBox::about(this,"注册失败","请输入至少4个长度的用户名");
        return;
    }else if(register_password.size()<8){
        QMessageBox::about(this,"注册失败","请输入至少8个长度的密码");
        return;
    }else{
        QString message = register_username;
        message+="注册成功";
        QMessageBox::about(this,"注册成功",message);
        textstr<<register_username<<" "<<register_password<<'\n';
        file.close();
        this->hide();
        emit show_login();
    }
}

void to_register::read_test(){
    QFile file(filename);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream textstr(&file);
    mp.clear();
    while (!textstr.atEnd()) {
        QString username;
        QString password;
        textstr>>username>>password;
        mp[username] = password;
//        qDebug()<<username<<password;
    }

    file.close();
}



void to_register::on_username_textChanged(const QString &arg1)
{
    register_username = arg1;
}

void to_register::on_password_textChanged(const QString &arg1)
{
    register_password = arg1;
}

void to_register::on_pushbutton_login_clicked()
{
    this->hide();
    emit show_login();
}

void to_register::on_pushbutton_register_clicked()
{
    register_account();
}


void to_register::paintEvent(QPaintEvent *event){
    // 背景图
    QPainter p(this); //创建画家，指定窗口为绘图设备
    p.setOpacity(0.5);
    p.drawPixmap(rect(), QPixmap(":/背景图/背景图/背景图8.png"));
}

void to_register::on_play_music_clicked()
{
    ui->play_music->hide();
    ui->stop_music->show();
    music_flag=0;
    emit stop_music();
}

void to_register::on_stop_music_clicked()
{
    ui->play_music->show();
    ui->stop_music->hide();
    music_flag = 1;
    emit play_music();
}
