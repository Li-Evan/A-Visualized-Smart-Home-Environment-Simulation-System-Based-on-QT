#include "start_page.h"
#include "ui_start_page.h"
extern int music_flag;

start_page::start_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start_page)
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


void start_page::paintEvent(QPaintEvent *event){
    // 背景图
    QPainter p(this); //创建画家，指定窗口为绘图设备
    p.setOpacity(0.5);
    p.drawPixmap(rect(), QPixmap(":/背景图及logo/开始页面"));
}


start_page::~start_page()
{
    delete ui;
}

void start_page::on_pushButton_clicked()
{
    this->hide();
    emit show_choose_info();
}

void start_page::receive_show(){
    if(music_flag==1){
        ui->play_music->show();
        ui->stop_music->hide();
    }else{
        ui->play_music->hide();
        ui->stop_music->show();
    }
    this->show();
}

void start_page::on_play_music_clicked()
{
    ui->play_music->hide();
    ui->stop_music->show();
    music_flag=0;
    emit stop_music();
}

void start_page::on_stop_music_clicked()
{
    ui->play_music->show();
    ui->stop_music->hide();
    music_flag = 1;
    emit play_music();
}
