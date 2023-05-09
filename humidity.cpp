//
// Created by LZP on 2022/5/25.
//

#include "humidity.h"
#include <QString>
#include <QDebug>
#include <random>
#include <time.h>
#define SEED (time(0)+(++tot_humi)*137)

using namespace std;

extern double air_room_capa; // 房间空调制冷量
extern double air_livingroom_capa; // 客厅空调制冷量
extern double humi_room_capa; // 房间加湿器加湿量
extern double humi_livingroom_capa; // 客厅加湿器加湿量
extern double new_wind_capa; // 新风
extern double floor_heating_capa; // 地暖



//// 湿度相关
extern map<int,pair<int,int>> tot_humidity_list; // 存放每季度平均湿度范围
extern map<string,map<int,double>> tot_rain_volume_map; // 存放每个城市各个季度降水量
extern map<string,int> tot_rain_day_map; // 存放各个城市一年下雨的总天数
extern map<string,map<int,double>> tot_rain_probability_map; // 存放各个城市各个季节降水的概率

extern vector<int> oneday_humidity_list; // 存放生成的一日湿度数据
extern map<int,int> rain_time; // 储存下雨的时间
extern map<int,int> light_time; // 储存打雷的时候
extern map<int,int> cloud_time; // 储存多云的时候

extern int season;
extern QString province;



//// 空气质量相关
extern map<string,pair<int,int>> tot_air_equality_list;  // 存放每个城市空气质量范围
extern vector<double> oneday_equaliy_list; // 存放生成的一日空气质量数据





//// 全局变量
int tot_humi = 0;


//// 通用计算函数
// 正态分布生成
double humi_norm_generate(double mu, double sigma, double limit) { // 生成正态分布的函数 三个参数分别为 均值 方差 异常值的接受程度
//    random_device rd;
//    default_random_engine rng{rd()}; // 为了生成值，可以将一个随机数生成器传给 norm 函数对象
    default_random_engine rng(SEED);//引擎
    normal_distribution<> norm{mu, sigma};
    double generate = 1000; // 先设定成一个异常值
    while (generate <= mu - limit * sigma || generate >= mu + limit * sigma) { // 如果发生小概率事件，生成的温度为异常值，则重新生成
        generate = norm(rng);
    }
    return generate;
}

// 平均分布生成(double)
double humi_uniform_double_generate(double minn,double maxx){
    default_random_engine rng(SEED);//引擎
    uniform_real_distribution<> uni_dis(minn, maxx);
    double ret = uni_dis(rng);
    return ret;
}

// 平均分布生成
int humi_uniform_int_generate(int minn,int maxx){

    default_random_engine rng(SEED*SEED);//引擎
    uniform_int_distribution<> uni_dis(minn, maxx);
    int ret = uni_dis(rng);

    return ret;
}

// 概率可控布尔值生成
bool humi_bool_possibility(double true_possibility){
    default_random_engine rng(SEED);//引擎
    bernoulli_distribution u(true_possibility);
    bool ret = u(rng);
    return ret;
}



//// 初始化工作
// 初始化每个季节的湿度取值范围
void init_humi_map(){
    tot_humidity_list[1] = {80,95};
    tot_humidity_list[2] = {80,95};
    tot_humidity_list[3] = {73,90};
    tot_humidity_list[4] = {68,85};
}

// 初始化各个城市每个季度的降水量
void init_rain_volume_map(){
    // 广东 828.8	581.15	363.47	159.51
    tot_rain_volume_map["广东"][1] = 828.8;
    tot_rain_volume_map["广东"][2] = 581.15;
    tot_rain_volume_map["广东"][3] = 363.47;
    tot_rain_volume_map["广东"][4] = 159.51;
    // 安徽 251.71	663.96	201.93	77.22
    tot_rain_volume_map["安徽"][1] =251.71;
    tot_rain_volume_map["安徽"][2] = 663.96;
    tot_rain_volume_map["安徽"][3] = 201.93;
    tot_rain_volume_map["安徽"][4] = 77.22;
    // 北京 74.68	310.64	100.58	42.67
    tot_rain_volume_map["北京"][1] = 74.68;
    tot_rain_volume_map["北京"][2] = 310.64;
    tot_rain_volume_map["北京"][3] = 100.58;
    tot_rain_volume_map["北京"][4] = 42.67;
    // 福建 423.16	742.44	203.96	101.35
    tot_rain_volume_map["福建"][1] = 423.16;
    tot_rain_volume_map["福建"][2] = 742.44;
    tot_rain_volume_map["福建"][3] = 203.96;
    tot_rain_volume_map["福建"][4] = 101.35;
    // 广西 196.09	492.0	257.56	84.07
    tot_rain_volume_map["广西"][1] = 196.09;
    tot_rain_volume_map["广西"][2] = 492.0;
    tot_rain_volume_map["广西"][3] = 257.56;
    tot_rain_volume_map["广西"][4] = 84.07;
}

// 初始化各个城市的降水天数
void init_rain_day_map(){
    // 广东
    tot_rain_day_map["广东"] = 155;
    // 安徽
    tot_rain_day_map["安徽"] = 138;
    // 北京
    tot_rain_day_map["北京"] = 79;
    // 福建
    tot_rain_day_map["福建"] = 126;
    // 广西
    tot_rain_day_map["广西"] = 135;
}

// 初始化各个城市各个季节的降水概率
// 初始化所有湿度情况调用该函数即可 该函数内调用了其他所有湿度有关的初始化函数
void init_rain_probability(){
    init_humi_map();
    init_rain_volume_map();
    init_rain_day_map();
    for(auto each:tot_rain_day_map){
        string city = each.first;
        double spring_rain_volume = tot_rain_volume_map[city][1];
        double summer_rain_volume = tot_rain_volume_map[city][2];
        double autumn_rain_volume = tot_rain_volume_map[city][3];
        double winter_rain_volume = tot_rain_volume_map[city][4];
        double sum_rain_volume = spring_rain_volume+summer_rain_volume+autumn_rain_volume+winter_rain_volume;
        tot_rain_probability_map[city][1] = tot_rain_day_map[city]*(spring_rain_volume/sum_rain_volume)/91;
        tot_rain_probability_map[city][2] = tot_rain_day_map[city]*(summer_rain_volume/sum_rain_volume)/91;
        tot_rain_probability_map[city][3] = tot_rain_day_map[city]*(autumn_rain_volume/sum_rain_volume)/91;
        tot_rain_probability_map[city][4] = tot_rain_day_map[city]*(winter_rain_volume/sum_rain_volume)/91;
    }
}


//// 正式生成湿度数据
// 生成一天基础湿度情况
// 进行初始化并生成 包含了全天湿度情况以及下雨情况 以及随机生成图标
void generate_oneday_basic_humidity(){
    // 初始化每个城市降雨概率 在初始化该概率的过程中就把所有跟湿度有关的量完成初始化了
    init_rain_probability();
    // 根据季节对应的湿度范围 生成一天的湿度情况
    int min_humi = tot_humidity_list[season].first;
    int max_humi = tot_humidity_list[season].second;
//    cout<<min_humi<<" "<<max_humi<<endl;
    oneday_humidity_list.push_back(0); // 0时是不存在的，随便搞个进去得了
    for (int i = 1; i <=24 ; ++i) {
        int cur_humi = humi_uniform_int_generate(min_humi,max_humi);

        oneday_humidity_list.push_back(cur_humi);
    }

    // 随机产生是否下雨 如果下雨随机产生下雨时间 修改下雨时间的湿度并将其储存到下雨时间vector里面
    int rain_flag = 0; // 0代表不下雨 1代表下雨
    double rain_possibility = tot_rain_probability_map[province.toStdString()][season]; // 该城市该季节的降水概率
    rain_flag = humi_bool_possibility(rain_possibility); // 生成今天是否下雨情况
    if (rain_flag){ // 如果下雨了 随机生成下雨的时间 rain_time里面存的时间是打雷，时间+1是下雨
        int bg_time = humi_uniform_int_generate(1,24);
        while (bg_time>=13 && bg_time<=18) bg_time = humi_uniform_int_generate(1,24);
        if (bg_time==24){
            rain_time[24]=1;
            light_time[23]=1;
            oneday_humidity_list[23] = 95;
            oneday_humidity_list[24] = 95;
        } else if(bg_time<=20){
            rain_time[bg_time+3]=1;
            light_time[bg_time+2] = 1;
            cloud_time[bg_time+1] = 1;
            cloud_time[bg_time] = 1;
            oneday_humidity_list[bg_time+3] = 95;
            oneday_humidity_list[bg_time+2] = 95;
        }
    }

    int bg_cloud_time = humi_uniform_int_generate(16,19);
    cloud_time[bg_cloud_time] = 1;
    cloud_time[bg_cloud_time+1] = 1;

}





// 初始化空气质量
void init_air_equality_list(){
    tot_air_equality_list["广东"] = {21,53};
    tot_air_equality_list["安徽"] = {25,100};
    tot_air_equality_list["北京"] = {37,100};
    tot_air_equality_list["福建"] = {22,65};
    tot_air_equality_list["广西"] = {23,76};
}

// 生成空气质量
void generate_oneday_air_equality(){
    init_air_equality_list();
    int minn = tot_air_equality_list[province.toStdString()].first;
    int maxx = tot_air_equality_list[province.toStdString()].second;
    oneday_equaliy_list.push_back(0);
    for (int i = 1; i <=24 ; ++i) {
        int cur_equality = humi_uniform_int_generate(minn,maxx);
        oneday_equaliy_list.push_back(cur_equality);
    }
}

void testt(){
    map<bool,int> mp;
    for (int i = 0; i < 100000; ++i) {
        bool bb = humi_bool_possibility(0.3);
        mp[bb]++;
    }
    for(auto mpp:mp){
        cout<<mpp.first<<" "<<mpp.second<<endl;
    }
}
