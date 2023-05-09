#ifndef FUNCTION_H
#define FUNCTION_H

#include <random>
#include <chrono>
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <cmath>
#include <QString>
#include <QDebug>
using namespace std;



// 测试接口
void test();

//// 初始化
// 初始化各城市各季度平均温度
void init_temp_map(map<string,map<int,double>>& tot_temperature_map);

// 初始化墙体编号与墙体材料关系
void init_material_correspondence_map(map<int, string> &material_correspondence_map);

// 初始化墙体材料的导热系数
void init_material_heat_conduction_map(map<string, double> &material_heat_conduction_map);

// 根据某个城市某个月份的平均温度生成某一天的24小时的温度
vector<double> set_24h_temperature(double ave_temperature);

// 开空调之后的温度变化
vector<double> temperature_change(double begin_temperature, double end_temperature,int model_id=2 );

vector<double> simulate_temporary_shutdown(double begin_temperature, double outside_temperature,
                                           double my_room_area, int material_id,int my_form_orientation,
                                           double my_wall_thickness = 0.24);

vector<double> generate_all();

void print_list(vector<double> to_print);

vector<double> air_conditioning_restart(double begin_temperature);


double caculate_energy_consumption(double power,double tot_time);



vector<double> caculate_energy_consumption();


#endif // FUNCTION_H
