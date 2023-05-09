#include "display_lcd.h"
#include "ui_display_lcd.h"
#include "function.h"
#include "humidity.h"
#include"energy_consumption.h"
#include <QMessageBox>
#include <QPainter>
#define cur_outside_temp oneday_temperature_list[(int)cur_time]
#define cur_outside_temp_hu oneday_temperature_list[(int)cur_time_humi]
#define cur_outside_humi oneday_humidity_list[(int)cur_time_humi]
#define tot_humidification_capacity (humi_room_capa*room_num+humi_livingroom_capa)
#define cur_outside_equality oneday_equaliy_list[(int)cur_time_equality]
extern int music_flag;

using namespace std;


extern double air_room_capa; // 房间空调制冷量
extern double air_livingroom_capa; // 客厅空调制冷量
extern double humi_room_capa; // 房间加湿器加湿量
extern double humi_livingroom_capa; // 客厅加湿器加湿量
extern double new_wind_capa; // 新风
extern double floor_heating_capa; // 地暖

extern double air_work_time; // 空调总工作时间
extern double humi_work_time; // 加湿器总工作时间
extern double new_wind_work_time; // 新风总工作时间


extern double tot_area; // 空间总面积
extern int room_num; // 房间数量
extern double tot_room_area; // 房间总面积
extern double livingroom_area; // 客厅总面积
extern int wall_marterial; // 墙体材料
extern int window_num; // 窗户数量
extern int orientation; // 房间朝向 东西走向升温较快 东西走向编号1 南北走向编号2

extern double begin_time; //开始模拟的时间


extern double goal_temp; // 空调降温降到的最适温度
extern vector<double> oneday_temperature_list; // 全天24小时的温度
extern double cur_time; // 生成所有温度列表过程中需要的辅助参数


//extern double tot_humidification_capacity; // 总额定加湿量
extern vector<int> oneday_humidity_list; // 全天24小时的湿度
double goal_humi = 65; // 设置加湿要达到的目标
double cur_time_humi;// 生成所有湿度列表过程中需要的辅助参数

double cur_time_equality; //生成所有空气质量列表过程中需要的辅助参数
extern vector<double> oneday_equaliy_list; // 存放生成的一日空气质量数据

// lcd_time 上展示的小时和分钟
int show_hour;
int show_minute = 0;


vector<double> all_temp; // 储存所有生成的变化的温度
vector<double> all_humi; // 储存所有生成的变化的湿度
vector<double> all_equality; // 储存所有生成的变化的空气质量
map<int,int> air_change_time; // 空调开启状态发生改变的时间
map<int,int> humi_change_time; // 加湿器开启状态发生改变的时间
map<int,int> equality_change_time; // 新风系统开启状态发生改变的时间

// 设定设备启动和关闭的标志图像
QString air_pic_path_default = ":/设备/image/空调 (1).png";

int air_flag = 1; // flag为1显示彩色图片 为-1显示黑白图片

QString humi_pic_path_default = ":/设备/image/加湿器黑白.png";
int humi_flag = -1;

QString new_wind_pic_path_default = ":/设备/image/空气清新器黑白.png";
int new_wind_flag = -1;





Display_LCD::Display_LCD(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Display_LCD)
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

Display_LCD::~Display_LCD()
{
    delete ui;
}

// 生成从进入那个时候到24时的全部温度数据，三分钟为间隔
void Display_LCD::generate_all_change(){
    all_temp.clear();
    // 设置当前时间为设置开始的时间
    cur_time = begin_time;
    // 外界温度高于27才开空调
    while (cur_outside_temp < 27){
        // 空调没开启 温度跟外界温度是一样的
        for(int i=0;i<20;i++){
            all_temp.push_back(cur_outside_temp);
        }
        cur_time+=1; // 过了1小时
        // 超过24时了，不用再生成了
        if (cur_time>24){
            return;
        }
    }

    // 处理空调初始启动
    vector<double> first_descend = temperature_change(cur_outside_temp,goal_temp);
    for(int i=0;i<first_descend.size()-1;i++){
        air_work_time+=3; // 空调总工作时间增加
        all_temp.push_back(first_descend[i]);
        all_temp.push_back((first_descend[i]+first_descend[i+1])/2); // 插一个中值，因为现在单位时间是3分钟
    }
    // 空调开启状态改变
    air_change_time[all_temp.size()-1]=1;

    // 设置当前的室内温度
    double cur_inside_temp = first_descend[first_descend.size()-1];

    // 处理空调在暂时关闭与重新启动之间的反复
    while (cur_time<24){
        //// 处理暂时关闭
        // 得到升温散点，时间的变化在函数中进行计算了
        vector<double> increase_temp = simulate_temporary_shutdown(cur_inside_temp,cur_outside_temp,tot_area,wall_marterial,orientation);
        for(int i=0;i<increase_temp.size();i+=3){
            all_temp.push_back(increase_temp[i]);
        }
        // 空调开启状态改变
        air_change_time[all_temp.size()-1]=1;

        //// 处理重新启动
        // 再重新启动之前检查一下是否达到关闭条件
        while (cur_outside_temp<25.5){ // 达到了关闭条件
            for(int i=0;i<20;i++){
                all_temp.push_back(cur_outside_temp);
            }
            cur_time+=1; // 过了1小时
            if (cur_time>24){
                return;
            }
        }

        // 设置当前室内温度
        cur_inside_temp = increase_temp[increase_temp.size()-1];
//          cur_inside_temp = increase_temp[increase_temp.size()-1];

        // 得到重新降温散点
        vector<double> decline = air_conditioning_restart(cur_inside_temp);
        for(int i=0;i<decline.size();i+=2){
//            qDebug()<<decline[i];
            air_work_time+=3; // 空调总工作时间增加
            all_temp.push_back(decline[i]);
        }
        // 空调开启状态改变
        air_change_time[all_temp.size()-1]=1;
        // 改变当前室内温度
        cur_inside_temp = decline[decline.size()-1];
    }
}

void Display_LCD::generate_all_humidity_change(){
    all_humi.clear();
    // 设置当前时间为开始模拟的时间
    cur_time_humi = begin_time;
    // 处理空调还未打开的情况
    while (cur_outside_temp_hu < 27){

        // 空调没开启 湿度跟外界湿度是一样的
        for(int i=0;i<20;i++){
            all_humi.push_back(cur_outside_humi);
        }
        cur_time_humi+=1; // 过了1小时
        // 超过24时了，不用再生成了
        if (cur_time_humi>24){
            return;
        }
    }

    double cur_inside_humi = cur_outside_humi;

    // 空调开后每分钟下降约1个相对湿度 因为lcd时间是以三分钟为单位的 所以下降2.8-3.2个相对湿度
    while (cur_inside_humi>=40){
        all_humi.push_back(cur_inside_humi);
        double to_minus = humi_uniform_double_generate(2.8,3.2);
        cur_inside_humi-=to_minus;
        cur_time_humi+=0.05; // 时间变化3分钟
    }

    // 加湿器开始在启动加湿和暂停房间减湿之间反复
    while (cur_time_humi<24){

        //// 加湿器启动 室内湿度上升
        double humi_coefficent = 20; // 该系数的含义是： 1平米空间上升1相对湿度所需的时间*每平米分到的加湿量
        double humi_linkage_efficiency = 0.8;
        double humi_coefficent_linkage = humi_coefficent*humi_linkage_efficiency; // 多设备情况下1平米空间上升1相对湿度所需的时间*每平米分到的加湿量
        double unit_capa = tot_humidification_capacity/tot_area; // 每平方米分到的加湿量
//        double to_add = 3*unit_capa/humi_coefficent_linkage; // 每三分钟增加的相对湿度
        double to_add = 3; // 每三分钟增加的相对湿度
        humi_change_time[all_humi.size()-1]=1;
        while (cur_inside_humi<=goal_humi){ // 未达到加湿目标就一直往上加
            humi_work_time+=3; // 加湿器工作时间增加
            all_humi.push_back(cur_inside_humi);
            cur_inside_humi+=to_add;
            cur_time_humi+=0.05;

        }
        //// 加湿器暂时休眠 如果空调还开着 室内湿度暂时下降 否则逐步回复到外界温度 速度都是每3分钟2.8-3.2个相对湿度
        humi_change_time[all_humi.size()-1]=1;
        if (cur_outside_temp_hu>=25.5){ // 如果空调还开着
//            qDebug()<<"空调还开着";
            while (cur_outside_temp_hu>=25.5 && cur_inside_humi>=50){
                all_humi.push_back(cur_inside_humi);
                double to_minus = humi_uniform_double_generate(2.8,3.2);
                cur_inside_humi-=to_minus;
                cur_time_humi+=0.05;
                if(cur_time_humi>=24) return;
            }
        } else{ // 外界温度太低，空调已经关闭
            while (cur_outside_temp_hu<25.5){ // 在空调还未重新开启之前 湿度应该一直上升直到跟外界一致
//                qDebug()<<cur_time_humi;
                if (cur_inside_humi<cur_outside_humi){ // 如果当前室内湿度小于外界湿度 就上升
                    all_humi.push_back(cur_inside_humi);
                    double add = humi_uniform_double_generate(1,2);
                    cur_inside_humi+=add;
                    if (cur_inside_humi>cur_outside_humi){
                        cur_inside_humi = cur_outside_humi;
                    }
                    cur_time_humi+=0.05;
                    if(cur_time_humi>=24) return;
                } else{ // 当前室内湿度已经和外界湿度一致，那就保持不变
                    all_humi.push_back(cur_inside_humi);
                    cur_time_humi+=0.05;
                    if(cur_time_humi>=24) return;
                }
            }
        }
    }
}


void Display_LCD::generate_all_equality_change(){
    all_equality.clear();
    // 设置当前时间为开始模拟的时间
    cur_time_equality = begin_time;

    while(cur_outside_equality<10){
        for(int i=0;i<20;i++){
            all_equality.push_back(cur_outside_equality);
        }
        cur_time_equality+=1;
    }
    
    double cur_inside_equality = cur_outside_equality;
    all_equality.push_back(cur_inside_equality);
    // 首次开启新风系统
    while (cur_inside_equality>5){
        new_wind_work_time+=3;
        cur_inside_equality-=humi_uniform_int_generate(2,4);
        if(cur_inside_equality<=1) cur_inside_equality=1;
        cur_time_equality+=0.05;
        all_equality.push_back(cur_inside_equality);
    }

    while (cur_time_equality<24) {
        equality_change_time[all_equality.size()-1] = 1;
        // 新风系统暂时关闭
        while (cur_inside_equality<20) {
           int add = humi_uniform_double_generate(2,4);
           cur_inside_equality+=add;
           cur_time_equality += 0.05;
           all_equality.push_back(cur_inside_equality);
        }
        equality_change_time[all_equality.size()-1] = 1;
        // 新风系统重新启动
        while(cur_inside_equality>5){
            new_wind_work_time+=3;
            int minus = humi_uniform_int_generate(2,4);
            cur_inside_equality-=minus;
            if(cur_inside_equality<=1) cur_inside_equality=1;
            cur_time_equality+=0.05;
            all_equality.push_back(cur_inside_equality);
        }
    }
}



void Display_LCD::timerEvent(QTimerEvent *event){
    if(event->timerId()==this->lcd_timer){ // 每个定时器周期执行一次
        //// 时间展示
        QString str;
        str+=QString::number(show_hour);
        str+=":";
        if(show_minute<10){
            str+="0";
            str+=QString::number(show_minute);
        }else{
            str+=QString::number(show_minute);
        }
        ui->lcd_time->display(str);
        show_minute+=3;
        if(show_minute>=60){
            show_minute-=60;
            show_hour+=1;
        }

        //// 室内温度示数展示
        static int temp_needle = 0;
        ui->lcd_inside_temp->display(all_temp[temp_needle++]);
        // 空调启动状态改变
        if(air_change_time[temp_needle]==1){
            air_flag*=-1;
        }


        //// 室内湿度示数展示
        static int humi_needle = 0;
        ui->lcd_inside_humi->display(all_humi[humi_needle++]);
        // 加湿器启动状态改变
        if(humi_change_time[humi_needle]==1){
            humi_flag*=-1;
        }

        //// 室内空气质量示数展示
        static int equality_needle = 0;
        ui->lcd_inside_equality->display(all_equality[equality_needle++]);
        if(equality_change_time[equality_needle]==1){
            new_wind_flag*=-1;
        }



        //// 室外温度示数展示

        ui->lcd_outside_temp->display(oneday_temperature_list[show_hour]);

        //// 室外湿度示数展示

        ui->lcd_outside_humi->display(oneday_humidity_list[show_hour]);

        //// 室外空气质量示数展示

        ui->lcd_outside_equality->display(oneday_equaliy_list[show_hour]);


        //// 结束计时器
        if(temp_needle==all_temp.size()-1){
            this->killTimer(this->lcd_timer);
        }
    }
}

void Display_LCD::paintEvent(QPaintEvent *event){

    // 背景图
    QPainter p(this); //创建画家，指定窗口为绘图设备
    p.setOpacity(0.5);
    p.drawPixmap(rect(), QPixmap(":/背景图及logo/开始页面"));
    //// 设备显示图片确定
    // 空调显示图片确定
    QString air_pic_path;
    if(air_flag==1){
        air_pic_path = ":/设备/image/空调 (1).png";
    }else {
        air_pic_path = ":/设备/image/空调黑白.png";
    }

    QPixmap *air_pixmap = new QPixmap(air_pic_path);
    air_pixmap->scaled(ui->label_air->size(), Qt::KeepAspectRatio);
    ui->label_air->setScaledContents(true);
    ui->label_air->setPixmap(*air_pixmap);
    
    // 加湿器显示图片确定
    QString humi_pic_path;
    if(humi_flag==1){
        humi_pic_path = ":/设备/image/加湿器.png";
    }else {
        humi_pic_path = ":/设备/image/加湿器黑白.png";
    }

    QPixmap *humi_pixmap = new QPixmap(humi_pic_path);
    humi_pixmap->scaled(ui->label_humi->size(), Qt::KeepAspectRatio);
    ui->label_humi->setScaledContents(true);
    ui->label_humi->setPixmap(*humi_pixmap);

    // 新风显示图片确定
    QString new_wind_pic_path;
    if(new_wind_flag==1){
        new_wind_pic_path = ":/设备/image/空气清新器.png";
    }else {
        new_wind_pic_path = ":/设备/image/空气清新器黑白.png";
    }

    QPixmap *new_wind_pixmap = new QPixmap(new_wind_pic_path);
    new_wind_pixmap->scaled(ui->label_equality->size(), Qt::KeepAspectRatio);
    ui->label_equality->setScaledContents(true);
    ui->label_equality->setPixmap(*new_wind_pixmap);
    
}



void Display_LCD::receive_show(){
    if(music_flag==1){
        ui->play_music->show();
        ui->stop_music->hide();
    }else{
        ui->play_music->hide();
        ui->stop_music->show();
    }
    this->show();
    generate_all_change();
    generate_all_humidity_change();
    generate_all_equality_change();
//    qDebug()<<all_temp.size();
//    qDebug()<<all_humi.size();
    qDebug()<<air_work_time;
    qDebug()<<humi_work_time;

    //// 设置各个设备最开始模拟的时候是开的还是关的
    // 空调
    if(all_temp[0]>27) air_flag=1;
    else air_flag = -1;
    // 加湿器
    humi_flag = -1; // 加湿器最开始一定是关的
    // 新风
    if(all_equality[0]>10) new_wind_flag=1;
    else new_wind_flag = -1;
    
    // 时钟
    show_hour = begin_time;
    cal_energy_consumption();
//    qDebug()<<air_room_consump;
//    qDebug()<<air_livingroom_consump;
//    qDebug()<<humi_room_consump;
//    qDebug()<<humi_livingroom_consump;
    // 开启定时器
    lcd_timer = this->startTimer(1000);
}

void Display_LCD::on_pushButton_clicked()
{
    this->hide();
    emit show_bingtu();
}

void Display_LCD::on_play_music_clicked()
{
    ui->play_music->hide();
    ui->stop_music->show();
    music_flag=0;
    emit stop_music();
}

void Display_LCD::on_stop_music_clicked()
{
    ui->play_music->show();
    ui->stop_music->hide();
    music_flag = 1;
    emit play_music();
}
