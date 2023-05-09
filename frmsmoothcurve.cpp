#include "frmsmoothcurve.h"
#include "ui_frmsmoothcurve.h"
#include "smoothcurve.h"
#include "qpainter.h"
#include "qdatetime.h"
#include "qdebug.h"
#include <QLabel>
#include <QString>
#include <QPalette>
#include <QToolTip>

#define TIMEMS QTime::currentTime().toString("hh:mm:ss zzz")
extern int music_flag;


extern vector<double> oneday_temperature_list; // 存放生成的当天的温度
extern vector<int> oneday_humidity_list; // 存放生成的当天湿度数据
extern vector<double> oneday_equaliy_list; // 存放生成的当天空气质量数据
extern map<int,int> rain_time; // 储存下雨的时间
extern map<int,int> light_time; // 储存打雷的时候
extern map<int,int> cloud_time; // 储存多云的时候

extern QString province;
extern int season;
extern double begin_time; //开始模拟的时间
QString bg_image = ":/背景图及logo/广州";

frmSmoothCurve::frmSmoothCurve(QWidget *parent) : QWidget(parent), ui(new Ui::frmSmoothCurve)
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

frmSmoothCurve::~frmSmoothCurve()
{
    delete ui;
}

void frmSmoothCurve::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //    painter.setRenderHint(QPainter::Antialiasing);

    //根据选择绘制不同的曲线路径
    painter.setPen(QPen(QColor(80, 80, 80), 5));
    if (ui->rbtnPathSmooth1->isChecked()) {
        painter.drawPath(pathSmooth1);
    } else if (ui->rbtnPathSmooth2->isChecked()) {
        painter.drawPath(pathSmooth2);
    } else {
        painter.drawPath(pathNormal);
    }

    // 如果曲线上的点可见则显示出来 否则不显示
    if (ui->ckShowPoint->isChecked()) {
        foreach(QLabel *label,hours_label_list){
            label->setVisible(true);
        }
    }else{
        foreach(QLabel *label,hours_label_list){
            label->setVisible(false);
        }
    }

    // 背景图
    QPainter p(this); //创建画家，指定窗口为绘图设备
    p.setOpacity(0.3);
    p.drawPixmap(rect(), QPixmap(bg_image));
}

void frmSmoothCurve::receive_show(){

    if(music_flag==1){
        ui->play_music->show();
        ui->stop_music->hide();
    }else{
        ui->play_music->hide();
        ui->stop_music->show();
    }
    // 根据选择的城市确定背景
    if(province=="广东") bg_image= ":/城市背景（24小时可视化）/image/广东广州.jpg";
    if(province=="广西") bg_image= ":/城市背景（24小时可视化）/image/广西巴泽.jpg";
    if(province=="安徽") bg_image= ":/城市背景（24小时可视化）/image/安徽宏村.jpg";

    // 一日温度，湿度，空气质量曲线
    vector<double> temperature = oneday_temperature_list;
    vector<int> humidity = oneday_humidity_list;
    vector<double> equality = oneday_equaliy_list;

    // 生成24个label控件存放到qlist里面
    for(int i=1;i<=24;i++){
        QLabel *t = new QLabel;
        hours_label_list<<t;

    }
    hours_label_list.toVector();


    // 图标图片及位置
    QString sun_path = ":/背景图及logo/太阳";
    QPixmap *sun_pixmap = new QPixmap(sun_path);
    QString light_path = ":/背景图及logo/打雷";
    QPixmap *light_pixmap = new QPixmap(light_path);
    QString rain_path = ":/背景图及logo/下雨";
    QPixmap *rain_pixmap = new QPixmap(rain_path);
    QString moon_path = ":/背景图及logo/月亮";
    QPixmap *moon_pixmap = new QPixmap(moon_path);
    QString cloud_path = ":/背景图及logo/多云";
    QPixmap *cloud_pixmap = new QPixmap(cloud_path);

    int move = height()-(temperature[1]*30)-500;
    for(int i = 1;i<=24;i++){

        // 设置这个时刻的天气图标应该是哪个
        QPixmap *cur_pixmap =sun_pixmap;
        if(rain_time[i]==1){
            cur_pixmap = rain_pixmap;
        }else if(light_time[i]==1){
            cur_pixmap = light_pixmap;
        }else if(cloud_time[i]==1){
            cur_pixmap = cloud_pixmap;
        }else if(i<=4 || i>=20){
            if(rain_time[i]!=1&&light_time[i]!=1&&cloud_time[i]!=1){
                cur_pixmap = moon_pixmap;
            }
        }

        // 设置坐标位置
        int x = 180+i*60,y = height()-(temperature[i]*30)-move;
        // int x = 500+i*35,y = temperature[i]*15;
        datas << QPointF(x,y);
        double round = 35;
        hours_label_list[i-1]->setGeometry(x-round/2,y-round/2,round,round);
        hours_label_list[i-1]->setParent(this);
        hours_label_list[i-1]->installEventFilter(this);

        // 设置悬浮提示文字
        QString str;
        str+=QString::number(i);
        str+="时\n";
        str+="温度:";
        str+=QString::number(temperature[i], 'f', 2);
        str+="℃\n";
        str+="相对湿度:";
        str+=QString::number(humidity[i]);
        str+="%\n";
        str+="空气质量指数(AQI):";
        str+=QString::number(equality[i]);


        // 改变QToolTip的样式
        QPalette palette = QToolTip::palette();
        palette.setColor(QPalette::Inactive,QPalette::ToolTipBase,Qt::white);   //设置ToolTip背景色
        palette.setColor(QPalette::Inactive,QPalette::ToolTipText,QColor(102, 102, 102, 255)); 	//设置ToolTip字体色
        QToolTip::setPalette(palette);
        QFont font("Segoe UI", -1, 50);
        font.setPixelSize(22);
        QToolTip::setFont(font);  //设置ToolTip字体
        hours_label_list[i-1]->setToolTip(str);

        // 设置图片自适应
        cur_pixmap->scaled(hours_label_list[i-1]->size(), Qt::KeepAspectRatio);
        hours_label_list[i-1]->setScaledContents(true);
        hours_label_list[i-1]->setPixmap(*cur_pixmap);
    }


    //正常曲线
    pathNormal.moveTo(datas.at(0));
    for (int i = 1; i < datas.size(); ++i) {
        pathNormal.lineTo(datas.at(i));
    }

    //平滑曲线1
    //qDebug() << TIMEMS << "createSmoothCurve start";
    pathSmooth1 = SmoothCurve::createSmoothCurve(datas);
    //qDebug() << TIMEMS << "createSmoothCurve stop";

    //平滑曲线2
    //qDebug() << TIMEMS << "createSmoothCurve2 start";
    pathSmooth2 = SmoothCurve::createSmoothCurve2(datas);
    //qDebug() << TIMEMS << "createSmoothCurve2 stop";

    // 默认显示坐标点
    ui->ckShowPoint->setChecked(true);

    // 将曲线链接方式与控件组合
    connect(ui->ckShowPoint, SIGNAL(clicked(bool)), this, SLOT(update()));
    connect(ui->rbtnPathNormal, SIGNAL(clicked(bool)), this, SLOT(update()));
    connect(ui->rbtnPathSmooth1, SIGNAL(clicked(bool)), this, SLOT(update()));
    connect(ui->rbtnPathSmooth2, SIGNAL(clicked(bool)), this, SLOT(update()));
    this->show();
}

// 事件过滤器
// 实现点击label跳转到页面
bool frmSmoothCurve::eventFilter(QObject *obj, QEvent *event)
{
    bool signal=false; // 记录是否有点击事件
    int num = 0; // 记录选择了第几个图标，第i个图标对应的是i+1时
    for(int i=0;i<hours_label_list.size();i++){
        auto choose_obj = hours_label_list.begin()+i;
        if(obj==*choose_obj){
            signal = true;
            num = i;
        }
    }

    if (signal) // 指定某个QLabel
    {

        if (event->type() == QEvent::MouseButtonPress) //鼠标点击跳转窗口
        {
            //            qDebug()<<num;
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换
            this->hide();
            begin_time = num+1;
            emit show_lcd();
            return true;

        }
        else
        {
            return false;
        }
    }
    else
    {
        // pass the event on to the parent class
        return QWidget::eventFilter(obj, event);
    }
}

//void frmSmoothCurve::on_return_button_clicked()
//{
//    this->hide();
//    emit return_page();
//}

void frmSmoothCurve::on_play_music_clicked()
{
    ui->play_music->hide();
    ui->stop_music->show();
    music_flag=0;
    emit stop_music();
}

void frmSmoothCurve::on_stop_music_clicked()
{
    ui->play_music->show();
    ui->stop_music->hide();
    music_flag = 1;
    emit play_music();
}
