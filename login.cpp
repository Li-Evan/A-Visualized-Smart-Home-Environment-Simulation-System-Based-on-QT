#include "login.h"
#include "ui_login.h"
#include <iostream>
#include <fstream>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QMessageBox>
#include <string>
#include <QPainter>
#include <map>
#define filename "userinfo.txt"
using namespace std;
extern int music_flag;

QString login_username;
QString login_password;

map<QString,QString> mp;

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
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

login::~login()
{
    delete ui;
}

void login::receive_show(){
    if(music_flag==1){
        ui->play_music->show();
        ui->stop_music->hide();
    }else{
        ui->play_music->hide();
        ui->stop_music->show();
    }
    this->show();
}

void login::read_user(){
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

void login::on_pushbutton_login_clicked()
{
    read_user();
    login_username = ui->username->text();
    login_password = ui->password->text();

    if(mp[login_username] == ""){
        QMessageBox::about(this,"登陆失败","用户名不存在");
    }else if(mp[login_username]!=login_password){
        QMessageBox::about(this,"登录失败","用户名密码不匹配");
    }else {
        QString message = "欢迎归来";
        message+=login_username;
        QMessageBox::about(this,"登录成功",message);
        this->hide();
        emit show_start_page();
    }
}

void login::on_pushbutton_register_clicked()
{
    this->hide();
    emit show_register();
}

void login::on_username_textEdited(const QString &arg1)
{
    login_username = arg1;
}

void login::on_password_textEdited(const QString &arg1)
{
    login_password = arg1;
}

void login::paintEvent(QPaintEvent *event){
    QPainter p(this);
    p.setOpacity(0.5);
    p.drawPixmap(rect(),QPixmap(":/背景图/背景图/背景图.png"));
}

void login::on_play_music_clicked()
{
    ui->play_music->hide();
    ui->stop_music->show();
    music_flag=0;
    emit stop_music();
}

void login::on_stop_music_clicked()
{
    ui->play_music->show();
    ui->stop_music->hide();
    music_flag = 1;
    emit play_music();
}
