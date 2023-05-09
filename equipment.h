#ifndef EQUIPMENT_H
#define EQUIPMENT_H


class air_conditioner{
public:
    double price; // 价格
    double pi; // 匹数
    double refrigerating_capacity; // 制冷量(W)
    double refrigerating_power; // 制冷功率
    double energy_efficiency_grade; // 能效等级
    air_conditioner(double myprice,double mypi,double myrefrigerating_capacity,
                    double myrefrigerating_power,double myenergy_efficiency_grade);
};

//// 海尔空调
class Haier:public air_conditioner{
public:
    Haier(double myprice,double mypi,double myrefrigerating_capacity,
          double myrefrigerating_power,double myenergy_efficiency_grade);
};

class KFR_35GW_05ED:public Haier{ // 劲享 1.5匹壁挂式变频空调（KFR-35GW/05EDS83套机A）
public:
    KFR_35GW_05ED();
};

class KFR_35GW_83U1:public Haier{ // 速享风 1.5匹壁挂式变频空调（KFR-35GW/83@U1-Ge）
public:
    KFR_35GW_83U1();
};

class KFR_72LW_81U1:public Haier{ // 荣御 3匹柜式变频空调（KFR-72LW/81@U1-Ub）
public:
    KFR_72LW_81U1();
};


class KFR_35GW_12KE:public Haier{ // 雷神者 1.5匹壁挂式变频空调（KFR-35GW/12KEA81U1）
public:
    KFR_35GW_12KE();
};

class KFR_26GW_B1KG:public Haier{ // 静悦 1匹壁挂式变频空调（KFR-26GW/B1KGC81U1）
public:
    KFR_26GW_B1KG();
};

class KFR_50LW_03KC:public Haier{ // 静悦 2匹柜式变频空调（KFR-50LW/03KCA81U1）
public:
    KFR_50LW_03KC();
};

//// 美的空调
class Midea:air_conditioner {
public:
    Midea(double myprice,double mypi,double myrefrigerating_capacity,
          double myrefrigerating_power,double myenergy_efficiency_grade);
};

class KFR_35GW_N8MX:public Midea{ // 美的旋耀1.5匹变频冷暖 （KFR-35GW/N8MXA1）
public:
    KFR_35GW_N8MX();
};

class KFR_35GW_BDN8:public Midea{ // 美的冷静星1.5匹变频智能空调挂机（KFR-35GW/BDN8Y-PH400(3)A）
public:
    KFR_35GW_BDN8();
};

class KFR_72LW_N8MJ:public Midea{ // 美的智行Ⅱ新3匹 变频冷暖柜机空调 （KFR-72LW/N8MJA3）
public:
    KFR_72LW_N8MJ();
};

class KFR_26GW_N8HF:public Midea{ // 华凌新三级能效 大1匹（KFR-26GW/N8HF3）
public:
    KFR_26GW_N8HF();
};

class KFR_35GW_N8MK:public Midea{ // 美的焕新风1.5匹一级（KFR-35GW/N8MKA1）
public:
    KFR_35GW_N8MK();
};

//// 松下空调

class Panasonic:air_conditioner{
public:
    Panasonic(double myprice,double mypi,double myrefrigerating_capacity,
          double myrefrigerating_power,double myenergy_efficiency_grade);
};

class SJG9KL1:public Panasonic{ // 松下（Panasonic）大1匹  SJG9KL1
public:
    SJG9KL1();
};

class SFY9KQ10:public Panasonic{ // 松下 新一级能效 1匹  SFY9KQ10
public:
    SFY9KQ10();
};

class R13KQ30:public Panasonic{ // 松下（Panasonic） 1.5匹  R13KQ30
public:
    R13KQ30();
};

class SFJY27FQ20N:public Panasonic{ // 松下适用二级能效 3匹 SFJY27FQ20N
public:
    SFJY27FQ20N();
};

#endif // EQUIPMENT_H
