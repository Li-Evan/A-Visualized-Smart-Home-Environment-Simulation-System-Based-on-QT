#include "choose_info.h"
#include "ui_choose_info.h"
#include <QGraphicsBlurEffect>
#include <QDebug>
#include <QMessageBox>
extern int music_flag;

// 跟空调模拟降温时长相关的参数
extern double tot_area; // 空间总面积
extern int room_num; // 房间数量
extern double tot_room_area; // 房间总面积
extern double livingroom_area; // 客厅总面积
extern int wall_marterial; // 墙体材料
extern int window_num; // 窗户数量
extern int orientation; // 房间朝向 东西走向升温较快 东西走向编号1 南北走向编号2
QString sss;

choose_info::choose_info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choose_info)
{
    ui->setupUi(this);

    ui->pushButton->show();
    ui->stop_button->hide();


}

void choose_info::paintEvent(QPaintEvent *event){
    QPainter p2(this);
    p2.drawPixmap(606,89,567,838,QPixmap(":/背景图及logo/image/图片1.png"));

    QPainter p(this);
    p.setOpacity(0.4);
    p.drawPixmap(rect(),QPixmap(":/背景图/背景图/背景图6.png"));
}



choose_info::~choose_info()
{
    delete ui;
}


void choose_info::receive_show(){
    if(music_flag==1){
        ui->pushButton->show();
        ui->stop_button->hide();
    }else{
        ui->pushButton->hide();
        ui->stop_button->show();
    }
    this->show();
}





//// 进行选项信息的获取

void choose_info::on_tot_area_textChanged(const QString &arg1)
{
    tot_area = arg1.toDouble();
//    qDebug()<<tot_area;
}

void choose_info::on_room_num_currentTextChanged(const QString &arg1)
{
    room_num = arg1.toInt();

}

void choose_info::on_room_area_textChanged(const QString &arg1)
{
    tot_room_area = arg1.toDouble();
}

void choose_info::on_livingroom_area_textChanged(const QString &arg1)
{
    livingroom_area = arg1.toDouble();
}

void choose_info::on_material_id_currentIndexChanged(int index)
{
    wall_marterial = index;

}


void choose_info::on_window_num_textChanged(const QString &arg1)
{
   window_num = arg1.toInt();
}

void choose_info::on_oriention_currentIndexChanged(int index)
{
    orientation = index;
//    qDebug()<<tot_area; // 空间总面积
//    qDebug()<<room_num; // 房间数量
//    qDebug()<<tot_room_area; // 房间总面积
//    qDebug()<<livingroom_area; // 客厅总面积
//    qDebug()<<wall_marterial; // 墙体材料
//    qDebug()<<window_num; // 窗户数量
//    qDebug()<<orientation; // 房间朝向 东西走向升温较快 东西走向编号1 南北走向编号2
}

void choose_info::on_wall_thickness_textChanged(const QString &arg1)
{
    sss = arg1;
}

void choose_info::on_oriention_currentIndexChanged(const QString &arg1)
{

}

void choose_info::on_pushButton_4_clicked()
{
    // 检查是否所有空都填上了合理的值
    if(!(tot_area>=70 && tot_area<=200)){
        QMessageBox::about(this,"非法信息","<font size='5'>空间总面积应该位于<br>70㎡到200㎡之间</font>");
        return;
    }else if(!(tot_room_area>=0.25*tot_area && tot_room_area<=0.5*tot_area)){
        QMessageBox::about(this,"非法信息","<font size='5'>房间总面积应该为空间总面积的0.25-0.5</font>");
        return;
    }else if(!(livingroom_area>=0.25*tot_area && livingroom_area<=0.5*tot_area)){
        QMessageBox::about(this,"非法信息","<font size='5'>客厅总面积应该为空间总面积的0.25-0.5</font>");
        return;
    }else if(!(livingroom_area+tot_room_area<=0.8*tot_area)){
        QMessageBox::about(this,"非法信息","<font size='5'>房间总面积加客厅面积应该不超过空间总面积的0.8</font>");
        return;
    }else if(!(window_num>=7 && window_num<=30)){
        QMessageBox::about(this,"非法信息","<font size='5'>窗户数量应该在7-30之间</font>");
        return;
    }

    // 检查所有空都填上了合理的值就进行页面跳转
    this->hide();
    emit show_choose_device();
}


// 播放--》暂停
void choose_info::on_pushButton_clicked()
{
    ui->pushButton->hide();
    ui->stop_button->show();
    music_flag=0;
    emit stop_music();
}

// 暂停--》播放
void choose_info::on_stop_button_clicked()
{
    ui->pushButton->show();
    ui->stop_button->hide();
    music_flag = 1;
    emit play_music();
}
