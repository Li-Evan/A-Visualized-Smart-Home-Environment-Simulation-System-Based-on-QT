#include "choose_city.h"
#include "ui_choose_city.h"
extern int music_flag;


extern QString province;
extern int quarter_id;



void choose_city::init_all_list(){

    // 初始化城市与对应位置关系
    auxiliary_map["广东"] = {1078,842};
    auxiliary_map["广西"] = {927,842};
    auxiliary_map["北京"] = {1135,414};
    auxiliary_map["安徽"] = {1179,625};
    auxiliary_map["福建"] = {1217,770};

    // 把城市名字和城市位置分别装进vector
    for(auto city:auxiliary_map){
//        qDebug()<<city.first;
        city_label_name.push_back(city.first);
        city_label_pos.push_back({city.second});
    }

    // 生成label
    for(int i=0;i < auxiliary_map.size();i++){
        QLabel *city_label = new QLabel;
        city_label->setParent(this);

        // 背景图片及自适应
        QString pic_path = ":/背景图及logo/地图logo";
        QPixmap *pixmap = new QPixmap(pic_path);
        pixmap->scaled(city_label->size(), Qt::KeepAspectRatio);
        city_label->setScaledContents(true);
        city_label->setPixmap(*pixmap);
        // 安装事件过滤器
        city_label->installEventFilter(this);
        // 设置tooltip
        city_label->setToolTip(city_label_name[i]);


        city_label_list<<city_label;
    }

    int map_logo_width = 50,map_logo_heigth=50;
    for(int i=0;i<auxiliary_map.size();i++){
        city_label_list[i]->setGeometry(city_label_pos[i].first-map_logo_width/2,
                                        city_label_pos[i].second-map_logo_heigth/2,
                                        map_logo_width,map_logo_heigth);
    }
}





choose_city::choose_city(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::choose_city)
{
    ui->setupUi(this);


    if(music_flag==1){
        ui->play_music->show();
        ui->stop_music->hide();
    }else{
        ui->play_music->hide();
        ui->stop_music->show();
    }

    init_all_list();

}



void choose_city::receive_show(){
    if(music_flag==1){
        ui->play_music->show();
        ui->stop_music->hide();
    }else{
        ui->play_music->hide();
        ui->stop_music->show();
    }
    this->show();  
}


// 重写绘画事件
void choose_city::paintEvent(QPaintEvent *event){
    // 背景图
    QPainter p(this); //创建画家，指定窗口为绘图设备
    p.setOpacity(0.7);
    p.drawPixmap(rect(), QPixmap(":/背景图及logo/image/中国地图.jpg"));
    for(int i=0;i<5;i++){
        city_label_list[i]->show();
    }
}

void choose_city::mousePressEvent(QMouseEvent *event){
    qDebug()<<event->x()<<event->y();
}


// 事件过滤器
// 实现点击label跳转窗口以及鼠标悬浮图片放大
bool choose_city::eventFilter(QObject *obj, QEvent *event)
{
    bool signal=false; // 记录是否有点击事件
    int num = 0; // 记录选择了第几个城市
    for(int i=0;i<city_label_list.size();i++){
        auto choose_obj = city_label_list.begin()+i;
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
            city_label_list[num]->move(city_label_list[num]->x()+25,city_label_list[num]->y()+25);
            city_label_list[num]->resize(50,50);
            this->hide();
            emit show_choose_season();
            province = city_label_name[num];
//            qDebug()<<province;

            return true;

        }
        else if (event->type() == QEvent::Enter) // 鼠标悬停放大
        {
            QEnterEvent *entereEvent = static_cast<QEnterEvent*>(event); // 事件转换
            city_label_list[num]->move(city_label_list[num]->x()-25,city_label_list[num]->y()-25);
            city_label_list[num]->resize(100,100);
            return true;

        }
        else if(event->type() == QEvent::Leave){ // 鼠标离开缩小
            city_label_list[num]->move(city_label_list[num]->x()+25,city_label_list[num]->y()+25);
            city_label_list[num]->resize(50,50);
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
        return QMainWindow::eventFilter(obj, event);
    }
}

choose_city::~choose_city()
{
    delete ui;
}


void choose_city::on_return_button_clicked()
{
    this->hide();
    emit return_page();
}

void choose_city::on_play_music_clicked()
{
    ui->play_music->hide();
    ui->stop_music->show();
    music_flag=0;
    emit stop_music();
}

void choose_city::on_stop_music_clicked()
{
    ui->play_music->show();
    ui->stop_music->hide();
    music_flag = 1;
    emit play_music();
}
