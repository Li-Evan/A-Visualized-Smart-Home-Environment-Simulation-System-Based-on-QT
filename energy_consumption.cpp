#include "energy_consumption.h"
#include <QDebug>


extern double air_room_capa; // 房间空调制冷量
extern double air_livingroom_capa; // 客厅空调制冷量
extern double humi_room_capa; // 房间加湿器加湿量
extern double humi_livingroom_capa; // 客厅加湿器加湿量
extern double new_wind_capa; // 新风
extern double floor_heating_capa; // 地暖

extern double air_work_time; // 空调总工作时间
extern double humi_work_time; // 加湿器总工作时间
extern double new_wind_work_time; // 新风总工作时间
extern double floor_heating_time; // 地暖总工作时间

extern double air_room_consump;
extern double air_livingroom_consump;
extern double humi_room_consump;
extern double humi_livingroom_consump;
extern double new_wind_consump;

void cal_energy_consumption(){
    // 房间空调
    air_room_consump = air_room_capa*air_work_time;
    air_room_consump/=60000;

    // 客厅空调
    air_livingroom_consump = air_livingroom_capa*air_work_time;
    air_livingroom_consump/=60000;

    // 房间加湿器
    humi_room_consump = humi_room_capa*humi_work_time;
    humi_room_consump/=60000;

    // 客厅加湿器
    humi_livingroom_consump = humi_livingroom_capa*humi_work_time;
    humi_livingroom_consump/=60000;

    // 新风
    new_wind_consump = new_wind_work_time*new_wind_capa;
    new_wind_consump/=60000;

//    qDebug()<<air_room_capa<<air_work_time;
//    qDebug()<<air_livingroom_capa<<air_work_time;
//    qDebug()<<humi_room_capa<<humi_work_time;
//    qDebug()<<humi_livingroom_capa<<humi_work_time;
//    qDebug()<<new_wind_capa<<new_wind_work_time;
//    qDebug()<<"---------------------------------------";

//    qDebug()<<air_room_consump;
//    qDebug()<<air_livingroom_consump;
//    qDebug()<<humi_room_consump;
//    qDebug()<<humi_livingroom_consump;
//    qDebug()<<new_wind_consump;
}
