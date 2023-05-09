//
// Created by LZP on 2022/5/5.
//
#include "function.h"
#include <QDebug>

#define SEED (time(0)+(++tot)*137)
#define tot_capacity air_room_capa*room_num+air_livingroom_capa

using namespace std;

extern QString province;
extern int season;

extern double air_room_capa; // 房间空调制冷量
extern double air_livingroom_capa; // 客厅空调制冷量
extern double humi_room_capa; // 房间加湿器加湿量
extern double humi_livingroom_capa; // 客厅加湿器加湿量
extern double new_wind_capa; // 新风
extern double floor_heating_capa; // 地暖

extern double air_work_time; // 空调总工作时间
extern double humi_work_time; // 加湿器总工作时间

//extern double tot_capacity;
//extern double equipment_num;
extern int room_num; // 房间数量

extern vector<double> oneday_temperature_list; // 存放生成的当天的温度
extern map<string,map<int,double>> tot_temperature_map; // 存放所有城市每季度平均温度
extern map<string ,double> material_heat_conduction_map; // 存放某种材料对应的热传导系数
extern map<int,string> material_correspondence_map; // 存放材料名称与材料编号的对应关系




extern double cur_time; // 当前时间

extern double goal_temp; // 空调降温降到的最适温度

extern double tot_area; // 空间总面积
extern int room_num; // 房间数量
extern double tot_room_area; // 房间总面积
extern double livingroom_area; // 客厅总面积
extern int wall_marterial; // 墙体材料
extern int window_num; // 窗户数量
extern int orientation; // 房间朝向 东西走向升温较快 东西走向编号1 南北走向编号2
extern double wall_thickness; // 墙体厚度


//// 全局变量
int tot=0; // 用于产生随机种子的全局变量
extern double tot_air_conditioner_time; // 统计空调累计运行时间

//// 参数初始化的工作
// 初始化所有城市每季度平均温度
void init_temp_map() {
    // 广东

    tot_temperature_map["广东"][1] = 25.18;
    tot_temperature_map["广东"][2] = 29.87;
    tot_temperature_map["广东"][3] = 25.21;
    tot_temperature_map["广东"][4] = 16.93;
    // 安徽
    tot_temperature_map["安徽"][1] = 16.53;
    tot_temperature_map["安徽"][2] = 27.13;
    tot_temperature_map["安徽"][3] = 18.27;
    tot_temperature_map["安徽"][4] = 6.46;
    // 北京
    tot_temperature_map["北京"][1] = 14.76;
    tot_temperature_map["北京"][2] = 25.62;
    tot_temperature_map["北京"][3] = 13.04;
    tot_temperature_map["北京"][4] = -1.43;
    // 福建 19.77	28.52	23.51	13.54
    tot_temperature_map["福建"][1] = 19.77;
    tot_temperature_map["福建"][2] = 28.52;
    tot_temperature_map["福建"][3] = 23.51;
    tot_temperature_map["福建"][4] = 13.54;
    // 广西 23.22	28.92	23.06	15.58
    tot_temperature_map["广西"][1] = 23.22;
    tot_temperature_map["广西"][2] = 28.92;
    tot_temperature_map["广西"][3] = 23.06;
    tot_temperature_map["广西"][4] = 15.58;
    // 贵州 15.76	23.83	16.14	7.01
    tot_temperature_map["贵州"][1] = 15.76;
    tot_temperature_map["贵州"][2] = 23.83;
    tot_temperature_map["贵州"][3] = 16.14;
    tot_temperature_map["贵州"][4] = 7.01;
    // 河北 16.27	27.09	15.3	3.14
    tot_temperature_map["河北"][1] = 16.27;
    tot_temperature_map["河北"][2] = 27.09;
    tot_temperature_map["河北"][3] = 15.31;
    tot_temperature_map["河北"][4] = 3.14;
    // 河南 16.82	27.5	16.37	5.59
    tot_temperature_map["河南"][1] = 16.82;
    tot_temperature_map["河南"][2] = 27.5;
    tot_temperature_map["河南"][3] = 16.37;
    tot_temperature_map["河南"][4] = 5.59;
    // 黑龙江 8.12	22.51	6.64	-15.44
    tot_temperature_map["黑龙江"][1] = 8.12;
    tot_temperature_map["黑龙江"][2] = 22.51;
    tot_temperature_map["黑龙江"][3] = 6.64;
    tot_temperature_map["黑龙江"][4] = -15.44;
    // 湖南 16.72	28.13	19.86	8.37
    tot_temperature_map["湖南"][1] = 16.72;
    tot_temperature_map["湖南"][2] = 28.13;
    tot_temperature_map["湖南"][3] = 19.86;
    tot_temperature_map["湖南"][4] = 8.37;
    // 吉林 9.29	22.57	7.52	-12.03
    tot_temperature_map["吉林"][1] = 9.29;
    tot_temperature_map["吉林"][2] = 22.57;
    tot_temperature_map["吉林"][3] = 7.52;
    tot_temperature_map["吉林"][4] = -12.03;
    // 江苏 16.82	27.27	19.07	6.58
    tot_temperature_map["江苏"][1] = 16.82;
    tot_temperature_map["江苏"][2] = 27.27;
    tot_temperature_map["江苏"][3] = 19.07;
    tot_temperature_map["江苏"][4] = 6.58;
    // 江西 18.31	29.17	21.41	9.81
    tot_temperature_map["江西"][1] = 18.31;
    tot_temperature_map["江西"][2] = 29.17;
    tot_temperature_map["江西"][3] = 21.41;
    tot_temperature_map["江西"][4] = 9.81;
    // 辽宁 10.93	23.49	9.82	-7.41
    tot_temperature_map["辽宁"][1] = 10.93;
    tot_temperature_map["辽宁"][2] = 23.49;
    tot_temperature_map["辽宁"][3] = 9.82;
    tot_temperature_map["辽宁"][4] = -7.41;
    // 内蒙古 8.01	20.49	5.88	-9.88
    tot_temperature_map["内蒙古"][1] = 8.01;
    tot_temperature_map["内蒙古"][2] = 20.49;
    tot_temperature_map["内蒙古"][3] = 5.88;
    tot_temperature_map["内蒙古"][4] = -9.88;
    // 青海 8.07	17.07	6.21	-4.41
    tot_temperature_map["青海"][1] = 8.07;
    tot_temperature_map["青海"][2] = 17.07;
    tot_temperature_map["青海"][3] = 6.21;
    tot_temperature_map["青海"][4] = -4.41;
    // 陕西 16.36	26.7	14.53	4.61
    tot_temperature_map["陕西"][1] = 16.36;
    tot_temperature_map["陕西"][2] = 26.7;
    tot_temperature_map["陕西"][3] = 14.53;
    tot_temperature_map["陕西"][4] = 4.61;
    // 上海 16.82	27.57	20.26	7.55
    tot_temperature_map["上海"][1] = 16.82;
    tot_temperature_map["上海"][2] = 27.57;
    tot_temperature_map["上海"][3] = 20.26;
    tot_temperature_map["上海"][4] = 7.55;
    // 四川 18.8	26.69	18.21	9.51
    tot_temperature_map["四川"][1] = 18.8;
    tot_temperature_map["四川"][2] = 26.69;
    tot_temperature_map["四川"][3] = 18.21;
    tot_temperature_map["四川"][4] = 9.51;
    // 湖北 17.27	28.44	19.42	7.84
    tot_temperature_map["湖北"][1] = 17.27;
    tot_temperature_map["湖北"][2] = 28.44;
    tot_temperature_map["湖北"][3] = 19.42;
    tot_temperature_map["湖北"][4] = 7.84;
    // 西藏 10.37	17.71	11.3	2.74
    tot_temperature_map["西藏"][1] = 10.37;
    tot_temperature_map["西藏"][2] = 17.71;
    tot_temperature_map["西藏"][3] = 11.3;
    tot_temperature_map["西藏"][4] = 2.74;
    // 新疆 12.16	26.48	9.12	-10.94
    tot_temperature_map["新疆"][1] = 12.16;
    tot_temperature_map["新疆"][2] = 26.48;
    tot_temperature_map["新疆"][3] = 9.12;
    tot_temperature_map["新疆"][4] = -10.94;
    // 云南 18.12	20.21	15.29	9.52
    tot_temperature_map["云南"][1] = 18.12;
    tot_temperature_map["云南"][2] = 20.21;
    tot_temperature_map["云南"][3] = 15.29;
    tot_temperature_map["云南"][4] = 9.52;
    // 浙江 18.24	28.37	20.62	8.51
    tot_temperature_map["浙江"][1] = 18.24;
    tot_temperature_map["浙江"][2] = 28.37;
    tot_temperature_map["浙江"][3] = 20.62;
    tot_temperature_map["浙江"][4] = 8.51;
}

// 初始化墙体编号与墙体材料关系
void init_material_correspondence_map() {
    material_correspondence_map[1] = "粘土多孔砖";
    material_correspondence_map[2] = "灰砂砖240";
    material_correspondence_map[3] = "炉渣砖240";
    material_correspondence_map[4] = "煤矸石烧结砖";
    material_correspondence_map[5] = "粉煤灰烧结砖";
    material_correspondence_map[6] = "混凝土双排孔砌块190";
    material_correspondence_map[7] = "混凝土多孔砖";
    material_correspondence_map[8] = "混凝土砌块内填膨胀珍珠岩（单排孔）";
    material_correspondence_map[9] = "煤矸石砌块内填膨胀珍珠岩";
    material_correspondence_map[10] = "ALC加气混凝土砌块";
    material_correspondence_map[11] = "粉煤灰加气混凝土砌块";
    material_correspondence_map[12] = "页岩模数烧结砖";
}

// 初始化墙体材料的导热系数
void init_material_heat_conduction_map() {
    // （W/mK）
    material_heat_conduction_map["粘土多孔砖"] = 0.58;
    material_heat_conduction_map["灰砂砖240"] = 1.10;
    material_heat_conduction_map["炉渣砖240"] = 0.81;
    material_heat_conduction_map["煤矸石烧结砖"] = 0.63;
    material_heat_conduction_map["粉煤灰烧结砖"] = 0.50;
    material_heat_conduction_map["混凝土双排孔砌块190"] = 0.68;
    material_heat_conduction_map["混凝土多孔砖"] = 0.80;
    material_heat_conduction_map["混凝土砌块内填膨胀珍珠岩（单排孔）"] = 0.33;
    material_heat_conduction_map["煤矸石砌块内填膨胀珍珠岩"] = 0.27;
    material_heat_conduction_map["ALC加气混凝土砌块"] = 0.20;
    material_heat_conduction_map["粉煤灰加气混凝土砌块"] = 0.22;
    material_heat_conduction_map["页岩模数烧结砖"] = 0.45;
}

//// 打印列表
void print_list(vector<double> to_print){
    for (auto each: to_print) {
        cout << each << endl;
    }
}

//// 通用计算函数
// 正态分布生成
double norm_generate(double mu, double sigma, double limit) { // 生成正态分布的函数 三个参数分别为 均值 方差 异常值的接受程度
    random_device rd;
//    default_random_engine rng{rd()}; // 为了生成值，可以将一个随机数生成器传给 norm 函数对象
    default_random_engine rng(SEED);//引擎
    normal_distribution<> norm{mu, sigma};
    double generate = 1000; // 先设定成一个异常值
    while (generate <= mu - limit * sigma || generate >= mu + limit * sigma) { // 如果发生小概率事件，生成的温度为异常值，则重新生成
        generate = norm(rng);
    }
    return generate;
}

// 产生概率转移的温度
array<double, 7> generate_die_value() {
    random_device rd;
//    default_random_engine rng{rd()};
    default_random_engine rng(SEED);//引擎
    uniform_real_distribution<> upos_one(0.9, 1.0);
    uniform_real_distribution<> upos_two(1.95, 2.05);
    uniform_real_distribution<> upos_three(2.96, 3.04);
    double pos_one = upos_one(rng);
    double pos_two = upos_two(rng);
    double pos_three = upos_three(rng);
    double neg_one = -upos_one(rng);
    double neg_two = -upos_two(rng);
    double neg_three = -upos_three(rng);
    array<double, 7> die_value{0, pos_one, pos_two, pos_three, neg_one, neg_two, neg_three};
    return die_value;
}


//// 全天温度生成函数
// 全天温度生成
vector<double> temperature_transfer(double ave_temperature) {

    // 生成全天核心温度
    double mu_tot = ave_temperature, sigma_tot = abs(mu_tot / 12); // mu:均值 sigma:方差
    double limit_tot = 1.5;
    double core_temperature = norm_generate(mu_tot, sigma_tot, limit_tot);

    // 0-8时的核心温度为全天核心温度-3
    double first_core_temperature = core_temperature - 3;
    double mu_first = first_core_temperature, sigma_first = abs(mu_first / 12); // mu:均值 sigma:方差
    double limit_first = 1.25;
    double first_begin_temperature = norm_generate(mu_first, sigma_first, limit_first);

    // 9-18时的核心温度为全天核心温度+3
    double second_core_temperature = core_temperature + 3;
    double mu_second = second_core_temperature, sigma_second = abs(mu_second / 12); // mu:均值 sigma:方差
    double limit_second = 1.25;
    double second_begin_temperature = norm_generate(mu_second, sigma_second, limit_second);

    // 19-23时的核心温度为全天核心温度-2
    double third_core_temperature = core_temperature - 2;
    double mu_third = third_core_temperature, sigma_third = abs(mu_third / 12); // mu:均值 sigma:方差
    double limit_third = 1.25;
    double third_begin_temperature = norm_generate(mu_third, sigma_third, limit_third);

    // 如果该天各阶段核心温度温差异常 则重新生成
    while (third_begin_temperature > second_begin_temperature - 2 ||
           third_begin_temperature < second_begin_temperature - 5 ||
           second_begin_temperature < first_begin_temperature + 2.5 ||
           second_begin_temperature > first_begin_temperature + 4 ||
           first_begin_temperature > third_begin_temperature - 0.5) { // 早上温度最低 下午最高 他们之间的温差应该在一定范围内 否则视为不合理
        first_begin_temperature = norm_generate(mu_first, sigma_first, limit_first);
        second_begin_temperature = norm_generate(mu_second, sigma_second, limit_second);
        third_begin_temperature = norm_generate(mu_third, sigma_third, limit_third);
    }

    // 现在需要根据各个阶段的核心温度生成出24小时的完整温度
    double pos_one = 0.5;
    double zero = 0.3;
    double pos_two = 0.12;
    double pos_three = 0.0095;
    double neg_one = 0.05;
    double neg_two = 0.02;
    double neg_three = 0.0005;

    // 温度小于核心温度时的转移概率
    array<double, 7> wts1 = {zero, pos_one, pos_two, pos_three, neg_one, neg_two, neg_three};
    discrete_distribution<size_t> d_smaller{begin(wts1), end(wts1)};

    // 温度大于核心温度时的转移概率
    array<double, 7> wts2 = {zero, neg_one, neg_two, neg_three, pos_one, pos_two, pos_three};
    discrete_distribution<size_t> d_bigger{begin(wts2), end(wts2)};

    // 随机生成器
    random_device rd;
//    default_random_engine rng{rd()};
    default_random_engine rng(SEED);//引擎

    // 依照转移概率的转移温度
    array<double, 7> die_value = generate_die_value();

    vector<double> oneday_temperature_list(25);
    oneday_temperature_list[1] = first_begin_temperature;
    for (int i = 2; i <= 8; ++i) {
        if (oneday_temperature_list[i - 1] < first_core_temperature) {
            oneday_temperature_list[i] = oneday_temperature_list[i - 1] + die_value[d_smaller(rng)];
        } else {
            oneday_temperature_list[i] = oneday_temperature_list[i - 1] + die_value[d_bigger(rng)];
        }
    }
    oneday_temperature_list[9] = min(second_begin_temperature, oneday_temperature_list[8] + 3);
    for (int i = 10; i <= 18; ++i) {
        if (oneday_temperature_list[i - 1] < second_core_temperature) {
            oneday_temperature_list[i] = oneday_temperature_list[i - 1] + die_value[d_smaller(rng)];
        } else {
            oneday_temperature_list[i] = oneday_temperature_list[i - 1] + die_value[d_bigger(rng)];
        }
    }
    oneday_temperature_list[19] = max(third_begin_temperature, oneday_temperature_list[18] - 2);
    for (int i = 20; i <= 24; ++i) {
        if (oneday_temperature_list[i - 1] < third_core_temperature) {
            oneday_temperature_list[i] = oneday_temperature_list[i - 1] + die_value[d_smaller(rng)];
        } else {
            oneday_temperature_list[i] = oneday_temperature_list[i - 1] + die_value[d_bigger(rng)];
        }
    }
    return oneday_temperature_list;
}

// 检查全天生成的温度是否合理
bool check_temperature(vector<double> v, double ave_temperature) {

    // 某个时段的温度异常
    for (int i = 1; i <= 8; ++i) {
        if (v[i] > ave_temperature - 1.5) {
            return false;
        }
    }
    for (int i = 9; i <= 18; ++i) {
        if (v[i] > ave_temperature + 6) {
            return false;
        }
    }
    for (int i = 19; i <= 24; ++i) {
        if (v[i] > ave_temperature - 1.5) {
            return false;
        }
    }

    // 全天温差过大
    if ((*max_element(v.begin() + 1, v.end()) - *min_element(v.begin() + 1, v.end())) > 9) return false;

    // 最大温度不在11-18时出现
    if (max_element(v.begin() + 1, v.end()) > v.begin() + 18 ||
        max_element(v.begin() + 1, v.end()) < v.begin() + 11)
        return false;
    return true;
}

// 生成全天温度主函数
// 返回值为全天温度列表(24个散点)
vector<double> set_24h_temperature(double ave_temperature) {

    // 生成全天温度
   vector<double> my_oneday_temperature_list = temperature_transfer(ave_temperature);

    // 通过检查函数检查生成的温度是否合理 不合理就重新生成
    while (!check_temperature(my_oneday_temperature_list, ave_temperature)) {
        my_oneday_temperature_list = temperature_transfer(ave_temperature);
    }

    return my_oneday_temperature_list;
}


//// 模拟开了空调之后温度变化
// 备选函数1：人口阻滞增长模型
double func_1(double x) { //r = 0.02735(0.0265, 0.0282); xm = 342.4(311, 373.8)
    double r = 0.02735; // (0.0265, 0.0282);
    double xm = 342.4; // (311, 373.8)
    double y = xm / (1 + (xm / 3.9 - 1) * exp(-r * (x - 1790)));
    return y;
}

// 调用备选函数生成温度变化率
vector<double> generate_temperature_change_rate() {
    map<int, double> mp;
    for (int i = 1790; i <= 2000; i += 10) {
        double before = func_1(double(i - 10));
        double now = func_1(double(i));
        double cc = (now - before) / now;
        mp[i] = cc / 24;
    }
    vector<double> temperature_change_rate;
    temperature_change_rate.push_back(mp[1990]);
    temperature_change_rate.push_back(mp[1960]);
    temperature_change_rate.push_back(mp[1940]);
    temperature_change_rate.push_back(mp[1870] + mp[2000]);
    temperature_change_rate.push_back(mp[1790] + mp[1980]);
    temperature_change_rate.push_back(mp[1820] + mp[1950]);
    temperature_change_rate.push_back(mp[1790] + mp[2000]);
    temperature_change_rate.push_back(mp[1790] + mp[1930]);
    temperature_change_rate.push_back(mp[1810] + mp[1990]);
    temperature_change_rate.push_back(mp[1790] + mp[2000]);
    temperature_change_rate.push_back(mp[1860] + mp[2000]);
    temperature_change_rate.push_back(mp[1950] + mp[2000]);
    temperature_change_rate.push_back(mp[1860] + mp[2000]);
    return temperature_change_rate;
}

// 空调制冷量与温度下降时间关系
// 计算单空间单设备制冷所需时间
// 参数解释：设备制冷量，空间面积，起始温度，最终温度
int caculate_single_time(double begin_temp,double end_temp){
    double ave_capa =  tot_capacity/tot_area;  // 平均每平米分到的制冷量
    double temp_coefficent = 2000; // 该系数的含义是： 1平米空间上升1度所需的时间*每平米分到的制冷量
    double change_temp = abs(begin_temp-end_temp);
    int time = int(temp_coefficent/ave_capa*change_temp);
    return time;
}

// 多设备联动制冷所需时间
// 参数解释：设备制冷量，空间面积，起始温度，最终温度,设备数量
// 参数与单设备完全一致，算法也基本一致
// 主要区别在于多设备联动会减少达到制定温度的时间
// 三个一匹的空调在三个位置同时启动，比一个1匹的空调启动，空间达到设定温度的时间更短
int caculate_multiple_time(double begin_temp,double end_temp){
    double ave_capa =  tot_capacity/tot_area;  // 平均每平米分到的制冷量
    double temp_coefficent = 2500; // 该系数的含义是： 1平米空间上升1度所需的时间*每平米分到的制冷量
    double linkage_efficiency = 0.92; // 每多一台设备会使总空间面积，总制冷量不变的情况下 达到指定的温度的时间减少的百分比
    double change_temp = abs(begin_temp-end_temp);
    double time = temp_coefficent/ave_capa*change_temp;
    time *= pow(linkage_efficiency,room_num);
    time = (int)time;
    return time;
}


// 真正生成温度变化曲线
// 约经过 time 时间 从 begin_temperature 变化到 end_temperature  一个单位时间是time/14
// 返回值是具体的温度变化散点列表
// 经过约13-18个单位时间（根据初始温度决定） 变化到最终温度
vector<double> temperature_change(double begin_temperature, double end_temperature,int model_id) {
    double time;
    if (model_id==1){ // 单设备单空间模式
        time = caculate_single_time(begin_temperature, end_temperature);
    } else{ // 多设备多空间模式
        time = caculate_multiple_time(begin_temperature,end_temperature);
    }

    vector<double> tot_temperature_change_rate = generate_temperature_change_rate();
    double unit_time = time / 14;

    // 生成三个阶段的变化率列表
    // 第一阶段变化率
    vector<double> begin_temperature_change_rate;  // size:3
    for (int i = 0; i <= 2; ++i) {
        begin_temperature_change_rate.push_back(tot_temperature_change_rate[i]);
    }
    vector<double> middle_temperature_change_rate;  // size:6
    // 第二阶段变化率
    for (int i = 3; i <= 8; ++i) {
        middle_temperature_change_rate.push_back(tot_temperature_change_rate[i]);
    }
    double temp = middle_temperature_change_rate[4];
    middle_temperature_change_rate[4] = middle_temperature_change_rate[5];
    middle_temperature_change_rate[5] = temp;
    // 第三阶段变化率
    vector<double> final_temperature_change_rate; // size:4
    for (int i = 9; i <= 12; ++i) {
        final_temperature_change_rate.push_back(tot_temperature_change_rate[i]);
    }

    // 每个阶段有一个阈值温度，低于这个温度就进入到下一个阶段
    /*
     * 刚开始开空调是第一阶段
     * 低于first_stage_threshold_temperature进入第二阶段
     * 低于second_stage_threshold_temperature进入第三阶段
     * 低于third_stage_threshold_temperature空调暂时停机
    */
    double tot_change_temperature = begin_temperature - end_temperature;
    double first_stage_change_rate = 0.1;
    double second_stage_change_rate = 0.65;
    double third_stage_change_rate = 0.25;
    double first_stage_threshold_temperature = begin_temperature - first_stage_change_rate * tot_change_temperature;
    double second_stage_threshold_temperature =
            begin_temperature - (first_stage_change_rate + second_stage_change_rate) * tot_change_temperature;
    double third_stage_threshold_temperature = begin_temperature - tot_change_temperature;
//    cout<<first_stage_threshold_temperature<<endl;
//    cout<<second_stage_threshold_temperature<<endl;
//    cout<<third_stage_threshold_temperature<<endl;

    // 分阶段降温
    vector<double> changed_temperature_list;
    double cur_temperature = begin_temperature;
    changed_temperature_list.push_back(cur_temperature);

    // 第一阶段
    // 第一阶段稳定花费两个单位时间去完成
    for (int i = 1; i < begin_temperature_change_rate.size(); ++i) {
        cur_temperature -= cur_temperature * begin_temperature_change_rate[i];
        changed_temperature_list.push_back(cur_temperature);
    }

    // 第二阶段
    // 第二阶段直至降低到阈值以下才开启第三阶段
    int second_change_rate_needle = 0;
    while (cur_temperature > second_stage_threshold_temperature) {
        if (second_change_rate_needle < middle_temperature_change_rate.size() - 1) {
            cur_temperature -= cur_temperature * middle_temperature_change_rate[second_change_rate_needle++];
        } else {
            cur_temperature -= cur_temperature * middle_temperature_change_rate[second_change_rate_needle];
        }
        changed_temperature_list.push_back(cur_temperature);
    }

    // 第三阶段
    // 第三阶段直至降到目标温度才关闭
    int third_change_rate_needle = 0;
    while (cur_temperature > third_stage_threshold_temperature) {
        if (third_change_rate_needle < final_temperature_change_rate.size() - 1) {
            cur_temperature -= cur_temperature * final_temperature_change_rate[third_change_rate_needle++];
        } else {
            cur_temperature -= cur_temperature * final_temperature_change_rate[third_change_rate_needle];
        }
        changed_temperature_list.push_back(cur_temperature);
    }

    // 增加空调累计运行时间
    tot_air_conditioner_time += time/60;

    // 增加当前时间
    cur_time += time/60;

    return changed_temperature_list;
}

// 空调停后温度上升辅助函数（热传导公式，计算单位时间升温）
double heat_conduction(double k, double area, double deta_t, double deta_l, int orientation) {
    // K为材料的热传导系数  0.2-1.1
    // 公式中A代表传热的面积(或是两物体的接触面积) 70-150
    // ΔT代表两端的温度差 2-9
    // ΔL则是两端的距离。
    double k_max = 1.1;
    double k_min = 0.2;
    double area_max = 70;
    double area_min = 150;
    double deta_t_max = 13;
    double deta_t_min = 0;

    double k_basics_weight = 16; //+7
    double area_basics_weight = 11; // +4
    double deta_t_basics_weight = 22; // +13
    double deta_l_basics_weight = 5;

    double k_advanced_weight = 7;
    double area_advanced_weight = 4;
    double deta_t_advanced_weight = 13;

    // 三个参数都是越大传热越快
    double k_point = (k - k_min) / (k_max - k_min);
    double area_point = (area - area_min) / (area_max - area_min);
    double deta_t_point = (deta_t - deta_t_min) / (deta_t_max - deta_t_min);

    double k_tot_weight = k_basics_weight + k_point * k_advanced_weight;
    double area_tot_weight = area_basics_weight + area_point * area_advanced_weight;
    double deta_t_tot_weight = deta_t_basics_weight + deta_t_point * deta_t_advanced_weight;
    double deta_l_tot_weight = deta_l_basics_weight;

    double fix_weight; // 根据房屋走向是否面向太阳进行修正，1是面朝太阳，2是不面朝太阳
    orientation == 1 ? fix_weight = 2 : fix_weight = 0;
    double scaling_factor = 0.00001; // 缩放因子
    return (k_tot_weight+area_tot_weight+deta_t_tot_weight+deta_l_tot_weight+fix_weight)*scaling_factor;
}

// 空调停后温度缓慢上升
// 单位时间：分钟
// 返回值是具体的温度变化散点列表
// 经过约25-35个单位时间（根据温差，房间面积，墙体材料，墙体厚度） 变化到重新启动空调温度
vector<double> simulate_temporary_shutdown(double begin_temperature, double outside_temperature,
                                           double my_room_area, int material_id,int my_form_orientation,
                                           double my_wall_thickness) {
    // 温度上升阈值（超过阈值后重新启动空调）
    double cur_temperature = begin_temperature;
//    double temperature_rise_threshold_rate = 0.0192;
//    double temperature_rise_threshold = begin_temperature * (1 + temperature_rise_threshold_rate);
    double  temperature_rise_threshold = 26.3;
    // 温差
    double temperature_difference = outside_temperature - begin_temperature;
    // 房间面积
    double room_area = my_room_area;
    // 热传导系数（W/mK）
    double thermal_conductivity = material_heat_conduction_map[material_correspondence_map[material_id]];
    // 窗体朝向（是否正对太阳）
    int form_orientation = orientation;
    // 墙体厚度已经在全局中定义


    // 一个单位时间改变的温度
    double unit_change_rate = (1+heat_conduction(thermal_conductivity, room_area, temperature_difference,
                                              wall_thickness, form_orientation));

    vector<double> increase_temperature_list;
    increase_temperature_list.push_back(cur_temperature);
    while (cur_temperature < temperature_rise_threshold) {
        cur_temperature *= unit_change_rate;
        increase_temperature_list.push_back(cur_temperature);
    }

    // 增加当前时间
    cur_time+=(double)increase_temperature_list.size()/60;

    return increase_temperature_list;
}

// 空调重新启动辅助函数（计算单位时间降温）
// time根据空调型号定为17-24min
double temperature_descend(double begin_temperature,double end_temperature,double time){
    return pow(end_temperature/begin_temperature,double(1/time));
}

// 空调重新启动函数
vector<double> air_conditioning_restart(double begin_temperature){
    // 温度下降阈值（低于阈值后空调重新休眠）
    double cur_temperature = begin_temperature;
    double temperature_change_threshold_rate = 0.0192;
    double temperature_descend_threshold = begin_temperature * (1 - temperature_change_threshold_rate*2);

    // 温度变化率和空调运行时间
//    qDebug()<<begin_temperature<<goal_temp;
//    double fate_time = caculate_multiple_time(begin_temperature,goal_temp);
    double change_rate = temperature_descend(begin_temperature,temperature_descend_threshold,17);
//    qDebug()<<time<<change_rate;
    // 生成温度变化离散散点（time个）
//    qDebug()<<temperature_descend_threshold;
    vector<double> descend_temperature_list;
    while (cur_temperature > temperature_descend_threshold){
        descend_temperature_list.push_back(cur_temperature);
        cur_temperature*=change_rate;
    }

    // 增加空调累计运行时间
    tot_air_conditioner_time += 17/60;
//    qDebug()<<tot_air_conditioner_time;


    // 增加当前时间
    cur_time+=17/60;

    return descend_temperature_list;
}



//// 计算空调功率
// 计算空调功率函数
// 参数解释：空调制冷功率 空调累计运行时间
// 返回值解释：耗电总量，以度为单位衡量
double caculate_energy_consumption(double power,double tot_time){
    return power/1000*tot_time/60;
}


vector<double> generate_all(){
    init_temp_map();
    init_material_correspondence_map();
    init_material_heat_conduction_map();

    oneday_temperature_list = set_24h_temperature(tot_temperature_map[province.toStdString()][season]);

//    print_list(oneday_temperature_list);
    return oneday_temperature_list;
}

vector<double> caculate_energy_consumption(){
    // 房间空调 客厅空调 房间加湿器 客厅加湿器
    vector<double> ret;
    ret.push_back(air_room_capa*air_work_time);
    ret.push_back(air_livingroom_capa*air_work_time);
    ret.push_back(humi_room_capa*humi_work_time);
    ret.push_back(humi_livingroom_capa*humi_work_time);
    return ret;
}





void test() {
    cout<<caculate_energy_consumption(750,30);

}
