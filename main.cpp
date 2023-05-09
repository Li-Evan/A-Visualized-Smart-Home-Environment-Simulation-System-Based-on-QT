#pragma execution_character_set("utf-8")

#include "frmsmoothcurve.h"
#include "display_lcd.h"
#include <QApplication>
#include <QTextCodec>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <QString>
#include "function.h"
#include "mainwindow.h"
#include "start_page.h"
#include "choose_city.h"
#include "choose_season.h"
#include "choose_device.h"
#include "choose_info.h"
#include "select_info.h"
#include "login.h"
#include "air_detail_info.h"
#include "humi_detail_info.h"
#include "to_register.h"
#include "mainwidget.h"
#include "play_music.h"


// 设备参数
double air_room_capa=2000; // 房间空调制冷量
double air_livingroom_capa=2250; // 客厅空调制冷量
double humi_room_capa=600; // 房间加湿器加湿量
double humi_livingroom_capa=600; // 客厅加湿器加湿量
double new_wind_capa=108; // 新风
double floor_heating_capa; // 地暖

double air_work_time; // 空调总工作时间
double humi_work_time; // 加湿器总工作时间
double new_wind_work_time; // 新风总工作时间
double floor_heating_time; // 地暖总工作时间

//double tot_capacity=18000; // 总额定制冷量（空调）
//double tot_humidification_capacity = 1400; // 总额定加湿量（加湿器）
//double equipment_num; // 空调数量
vector<double> oneday_temperature_list; // 存放生成的当天的温度
map<string,map<int,double>> tot_temperature_map; // 存放所有城市每季度平均温度
map<string ,double> material_heat_conduction_map; // 存放某种材料对应的热传导系数
map<int,string> material_correspondence_map; // 存放材料名称与材料编号的对应关系

// 启动模拟的参数
QString province;
int season;
double begin_time; //开始模拟的时间

double tot_air_conditioner_time = 0; // 空调累计运行时间

double cur_time; // 当前时间

// 跟空调模拟降温时长相关的参数
double tot_area=130; // 空间总面积
int room_num=3; // 房间数量
double tot_room_area=60; // 房间总面积
double livingroom_area=40; // 客厅总面积
int wall_marterial=2; // 墙体材料
int window_num=10; // 窗户数量
int orientation=1; // 房间朝向 东西走向升温较快 东西走向编号1 南北走向编号2
double wall_thickness=0.24; // 墙体厚度

double goal_temp = 26; // 空调降温降到的最适温度

QString room_air_model; // 房间空调型号
QString livingroom_air_model; // 客厅空调型号

//// 湿度相关
vector<int> oneday_humidity_list; // 存放生成的一日湿度数据
map<int,pair<int,int>> tot_humidity_list; // 存放每季度平均湿度范围
map<string,map<int,double>> tot_rain_volume_map; // 存放每个城市各个季度降水量
map<string,int> tot_rain_day_map; // 存放各个城市一年下雨的总天数
map<string,map<int,double>> tot_rain_probability_map; // 存放各个城市各个季节降水的概率

map<int,int> rain_time; // 储存下雨的时间
map<int,int> light_time; // 储存打雷的时候
map<int,int> cloud_time; // 储存多云的时候

//// 空气质量相关
map<string,pair<int,int>> tot_air_equality_list;  // 存放每个城市空气质量范围
vector<double> oneday_equaliy_list; // 存放生成的一日空气质量数据

//// 总体能耗计算
double air_room_consump;
double air_livingroom_consump;
double humi_room_consump;
double humi_livingroom_consump;
double new_wind_consump;


// 音乐是否开启的状态
int music_flag = 1; // 0表示关 1表示开



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font;
    font.setFamily("Microsoft Yahei");
    font.setPixelSize(13);
    a.setFont(font);

    //// 各个窗口
    // 播放音乐窗口（永远不会显示！）
    play_music w_play_music;

    // 登录界面
    login w_login;
    w_login.setFixedSize(1800,1000);
    w_login.setWindowTitle("登录页面");
    w_login.show();

    // 注册界面
    to_register w_to_register;
    w_to_register.setFixedSize(1800,1000);
    w_to_register.setWindowTitle("注册页面");

    // 开始页面窗口
    start_page w_start_page;
    w_start_page.setFixedSize(1800,1000);
    w_start_page.setWindowTitle("开始页面");
//    w_start_page.show();

    // 空间信息设置窗口
    choose_info w_choose_info;
    w_choose_info.setFixedSize(1800,1000);
    w_choose_info.setWindowTitle("空间信息选择");
//    w_choose_info.show();

    // 设备选择窗口
    choose_device w_choose_device;
    w_choose_device.setFixedSize(1800,1000);
    w_choose_device.setWindowTitle("设备选择");
//    w_choose_device.show();

    // 空调详细信息页面
    air_detail_info w_air_detail_info;
    w_air_detail_info.setFixedSize(900,800);
    w_air_detail_info.setWindowTitle("空调详情");
//    w_air_detail_info.show();

    // 加湿器详细信息页面
    humi_detail_info w_humi_detail_info;
    w_humi_detail_info.setFixedSize(900,1000);
    w_humi_detail_info.setWindowTitle("加湿器详情");
//    w_humi_detail_info.show();

    // 城市选择窗口
    choose_city w_choose_city;
    w_choose_city.setFixedSize(1800,1000);
    w_choose_city.setWindowTitle("城市选择页面");

    // 季节选择窗口
    choose_season w_choose_season;
    w_choose_season.setFixedSize(1800,1000);
    w_choose_season.setWindowTitle("季节选择页面");

    // 24小时温度可视化窗口
    frmSmoothCurve w_frmsmoothcurve;
    w_frmsmoothcurve.setFixedSize(1800,1000);
    w_frmsmoothcurve.setWindowTitle("24小时温度可视化表示");
//    w_frmsmoothcurve.show();

    // 空调lcd窗口
    Display_LCD w_display_lcd;
    w_display_lcd.setFixedSize(1800,1000);
    w_display_lcd.setWindowTitle("空调打开后的温度变化");
//    w_display_lcd.show();

    // 饼图能耗窗口
    MainWidget w_display_pie;
    w_display_pie.setFixedSize(1800,1000);
    w_display_pie.setWindowTitle("总体能耗饼图展示");

    // 各个窗口之间的槽函数

    // 连接登录页面和开始页面
    QObject::connect(&w_login, SIGNAL(show_start_page()),
                     &w_start_page,SLOT(receive_show()));

    // 连接登录页面和注册页面
    QObject::connect(&w_login, SIGNAL(show_register()),
                     &w_to_register,SLOT(receive_show()));

    // 连接注册页面和开始页面
    QObject::connect(&w_to_register, SIGNAL(show_login()),
                     &w_login,SLOT(receive_show()));

    // 连接开始页面与选择信息页面
    QObject::connect(&w_start_page, SIGNAL(show_choose_info()),
                     &w_choose_info,SLOT(receive_show()));

    // 连接选择信息与选择设备信息页面
    QObject::connect(&w_choose_info, SIGNAL(show_choose_device()),
                     &w_choose_device,SLOT(receive_show()));


    // 连接选择设备信息页面和选择城市页面
    QObject::connect(&w_choose_device, SIGNAL(show_choose_city()),
                     &w_choose_city,SLOT(receive_show()));

    // 连接选择城市页面和选择季节页面
    QObject::connect(&w_choose_city, SIGNAL(show_choose_season()),
                     &w_choose_season,SLOT(receive_show()));


    // 连接选择季节页面和24小时温度可视化展示页面
    QObject::connect(&w_choose_season, SIGNAL(show_smoothcurve()),
                     &w_frmsmoothcurve,SLOT(receive_show()));


    // 连接24小时温度可视化展示页面和lcd展示温度变化页面
    QObject::connect(&w_frmsmoothcurve, SIGNAL(show_lcd()),
                     &w_display_lcd,SLOT(receive_show()));


    // 连接lcd展示页面和饼图展示页面
    QObject::connect(&w_display_lcd,SIGNAL(show_bingtu()),
                     &w_display_pie,SLOT(receive_show()));

    //// 点击设备图片弹出设备具体信息
    // 空调
    QObject::connect(&w_choose_device,SIGNAL(show_air()),
                     &w_air_detail_info,SLOT(receive_show()));

    // 加湿器
    QObject::connect(&w_choose_device,SIGNAL(show_humi()),
                     &w_humi_detail_info,SLOT(receive_show()));

    //// 返回上一页的逻辑
    // 连接选择设备信息与选择空间信息页面
    QObject::connect(&w_choose_device,SIGNAL(return_page()),
                     &w_choose_info,SLOT(receive_show()));


    // 连接选择城市信息与选择设备信息页面
    QObject::connect(&w_choose_city,SIGNAL(return_page()),
                     &w_choose_device,SLOT(receive_show()));

    // 连接24小时温度可视化页面和选择季节页面
    QObject::connect(&w_frmsmoothcurve, SIGNAL(return_page()),
                     &w_choose_season,SLOT(receive_show()));

    // 连接选择季节页面和选择城市页面
    QObject::connect(&w_choose_season, SIGNAL(return_page()),
                     &w_choose_city,SLOT(receive_show()));


    //// 暂停开启音乐的逻辑
    QObject::connect(&w_login, SIGNAL(stop_music()),
                     &w_play_music,SLOT(receive_stop_music()));
    QObject::connect(&w_login, SIGNAL(play_music()),
                     &w_play_music,SLOT(receive_play_music()));

    QObject::connect(&w_to_register, SIGNAL(stop_music()),
                     &w_play_music,SLOT(receive_stop_music()));
    QObject::connect(&w_to_register, SIGNAL(play_music()),
                     &w_play_music,SLOT(receive_play_music()));

    QObject::connect(&w_start_page, SIGNAL(stop_music()),
                     &w_play_music,SLOT(receive_stop_music()));
    QObject::connect(&w_start_page, SIGNAL(play_music()),
                     &w_play_music,SLOT(receive_play_music()));

    QObject::connect(&w_choose_info, SIGNAL(stop_music()),
                     &w_play_music,SLOT(receive_stop_music()));
    QObject::connect(&w_choose_info, SIGNAL(play_music()),
                     &w_play_music,SLOT(receive_play_music()));

    QObject::connect(&w_choose_device, SIGNAL(stop_music()),
                     &w_play_music,SLOT(receive_stop_music()));
    QObject::connect(&w_choose_device, SIGNAL(play_music()),
                     &w_play_music,SLOT(receive_play_music()));

    QObject::connect(&w_choose_city, SIGNAL(stop_music()),
                     &w_play_music,SLOT(receive_stop_music()));
    QObject::connect(&w_choose_city, SIGNAL(play_music()),
                     &w_play_music,SLOT(receive_play_music()));

    QObject::connect(&w_choose_season, SIGNAL(stop_music()),
                     &w_play_music,SLOT(receive_stop_music()));
    QObject::connect(&w_choose_season, SIGNAL(play_music()),
                     &w_play_music,SLOT(receive_play_music()));

    QObject::connect(&w_display_lcd, SIGNAL(stop_music()),
                     &w_play_music,SLOT(receive_stop_music()));
    QObject::connect(&w_display_lcd, SIGNAL(play_music()),
                     &w_play_music,SLOT(receive_play_music()));

    return a.exec();
}
