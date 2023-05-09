#include "choose_device.h"
#include "ui_choose_device.h"
extern int music_flag;

extern double air_room_capa; // 房间空调制冷量
extern double air_livingroom_capa; // 客厅空调制冷量
extern double humi_room_capa; // 房间加湿器加湿量
extern double humi_livingroom_capa; // 客厅加湿器加湿量
extern double new_wind_capa; // 新风
extern double floor_heating_capa; // 地暖

choose_device::choose_device(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choose_device)
{
    ui->setupUi(this);

    if(music_flag==1){
        ui->play_music->show();
        ui->stop_music->hide();
    }else{
        ui->play_music->hide();
        ui->stop_music->show();
    }

    QString room_air_path = ":/设备/image/房间空调型号.png";
    QPixmap *room_air_pixmap = new QPixmap(room_air_path);
    room_air_pixmap->scaled(ui->room_air_label->size(), Qt::KeepAspectRatio);
    ui->room_air_label->setScaledContents(true);
    ui->room_air_label->setPixmap(*room_air_pixmap);
    ui->room_air_label->installEventFilter(this);

    QString livingroom_air_path = ":/设备/image/客厅空调型号.png";
    QPixmap *livingroom_air_pixmap = new QPixmap(livingroom_air_path);
    livingroom_air_pixmap->scaled(ui->livingroom_air_label->size(), Qt::KeepAspectRatio);
    ui->livingroom_air_label->setScaledContents(true);
    ui->livingroom_air_label->setPixmap(*livingroom_air_pixmap);
    ui->livingroom_air_label->installEventFilter(this);

    QString Humidifier_path = ":/设备/image/房间加湿器.png";
    QPixmap *Humidifier_pixmap = new QPixmap(Humidifier_path);
    Humidifier_pixmap->scaled(ui->Humidifier_label->size(), Qt::KeepAspectRatio);
    ui->Humidifier_label->setScaledContents(true);
    ui->Humidifier_label->setPixmap(*Humidifier_pixmap);
    ui->Humidifier_label->installEventFilter(this);

    QString livingroom_Humidifier_path = ":/设备/image/客厅加湿器.png";
    QPixmap *livingroom_Humidifier_pixmap = new QPixmap(livingroom_Humidifier_path);
    livingroom_Humidifier_pixmap->scaled(ui->livingroom_Humidifier_label->size(), Qt::KeepAspectRatio);
    ui->livingroom_Humidifier_label->setScaledContents(true);
    ui->livingroom_Humidifier_label->setPixmap(*livingroom_Humidifier_pixmap);
    ui->livingroom_Humidifier_label->installEventFilter(this);

    QString new_wind_path = ":/设备/image/新风型号.png";
    QPixmap *new_wind_pixmap = new QPixmap(new_wind_path);
    new_wind_pixmap->scaled(ui->new_wind_label->size(), Qt::KeepAspectRatio);
    ui->new_wind_label->setScaledContents(true);
    ui->new_wind_label->setPixmap(*new_wind_pixmap);
    ui->new_wind_label->installEventFilter(this);

    QString floor_heating_path = ":/设备/image/地暖型号final.png";
    QPixmap *floor_heating_pixmap = new QPixmap(floor_heating_path);
    new_wind_pixmap->scaled(ui->floor_heating_label->size(), Qt::KeepAspectRatio);
    ui->floor_heating_label->setScaledContents(true);
    ui->floor_heating_label->setPixmap(*floor_heating_pixmap);
    ui->floor_heating_label->installEventFilter(this);




    ui->air_comboBox->setCurrentIndex(-1);
    ui->air_comboBox_2->setCurrentIndex(-1);
    ui->air_comboBox_3->setCurrentIndex(-1);
    ui->air_comboBox_4->setCurrentIndex(-1);
    ui->air_comboBox_5->setCurrentIndex(-1);
    ui->air_comboBox_6->setCurrentIndex(-1);

}



choose_device::~choose_device()
{
    delete ui;
}


void choose_device::paintEvent(QPaintEvent *event){
    QPainter p(this);
    p.setOpacity(0.4);
    p.drawPixmap(rect(),QPixmap(":/背景图及logo/image/家居背景4.jpg"));
}


void choose_device::on_air_comboBox_currentIndexChanged(int index)
{
    // 显示图片
    if (index>=0){
        QString pic_path = ":/设备/image/空调 (1).png";
        QPixmap *pixmap = new QPixmap(pic_path);
        pixmap->scaled(ui->room_air_label->size(), Qt::KeepAspectRatio);
        ui->room_air_label->setScaledContents(true);
        ui->room_air_label->setPixmap(*pixmap);
    }

    // 修改全局参数
    if(index==1) air_room_capa = 2500;
    if(index==2) air_room_capa = 2500;
    if(index==3) air_room_capa = 2500;
    if(index==4) air_room_capa = 1600;
    if(index==5) air_room_capa = 3100;
    if(index==5) air_room_capa = 2500;
    if(index==6) air_room_capa = 2510;
    if(index==7) air_room_capa = 1600;
    if(index==8) air_room_capa = 2500;
    if(index==9) air_room_capa = 1600;
    if(index==10) air_room_capa = 1600;
    if(index==11) air_room_capa = 2500;

}

void choose_device::on_air_comboBox_2_currentIndexChanged(int index)
{
    if (index>=0){
        QString pic_path = ":/设备/image/立式空调.png";
        QPixmap *pixmap = new QPixmap(pic_path);
        pixmap->scaled(ui->livingroom_air_label->size(), Qt::KeepAspectRatio);
        ui->livingroom_air_label->setScaledContents(true);
        ui->livingroom_air_label->setPixmap(*pixmap);
    }

    if(index==1) air_livingroom_capa = 5220;
    if(index==2) air_livingroom_capa = 5200;
    if(index==3) air_livingroom_capa = 5200;
}

void choose_device::on_air_comboBox_3_currentIndexChanged(int index)
{
    if (index>=0){
        QString pic_path = ":/设备/image/加湿器.png";
        QPixmap *pixmap = new QPixmap(pic_path);
        pixmap->scaled(ui->Humidifier_label->size(), Qt::KeepAspectRatio);
        ui->Humidifier_label->setScaledContents(true);
        ui->Humidifier_label->setPixmap(*pixmap);
    }

    if(index==1) humi_room_capa = 250;
    if(index==2) humi_room_capa = 250;
    if(index==3) humi_room_capa = 280;
    if(index==4) humi_room_capa = 300;
    if(index==5) humi_room_capa = 280;
    if(index==6) humi_room_capa = 240;
    if(index==7) humi_room_capa = 300;
    if(index==8) humi_room_capa = 300;
    if(index==9) humi_room_capa = 300;
}


void choose_device::on_air_comboBox_5_currentIndexChanged(int index)
{
    if (index>=0){
        QString pic_path = ":/设备/image/空气清新器.png";
        QPixmap *pixmap = new QPixmap(pic_path);
        pixmap->scaled(ui->new_wind_label->size(), Qt::KeepAspectRatio);
        ui->new_wind_label->setScaledContents(true);
        ui->new_wind_label->setPixmap(*pixmap);
    }
    if(index==1) new_wind_capa = 310;
    if(index==2) new_wind_capa = 250;
    if(index==3) new_wind_capa = 310;
    if(index==4) new_wind_capa = 360;
    if(index==5) new_wind_capa = 350;

}

void choose_device::on_air_comboBox_6_currentIndexChanged(int index)
{
    if (index>=0){
        QString pic_path = ":/设备/image/地暖.png";
        QPixmap *pixmap = new QPixmap(pic_path);
        pixmap->scaled(ui->floor_heating_label->size(), Qt::KeepAspectRatio);
        ui->floor_heating_label->setScaledContents(true);
        ui->floor_heating_label->setPixmap(*pixmap);
    }
}


void choose_device::on_air_comboBox_4_currentIndexChanged(int index)
{
    if (index>=0){
        QString pic_path = ":/设备/image/客厅加湿器.jpg";
        QPixmap *pixmap = new QPixmap(pic_path);
        pixmap->scaled(ui->livingroom_Humidifier_label->size(), Qt::KeepAspectRatio);
        ui->livingroom_Humidifier_label->setScaledContents(true);
        ui->livingroom_Humidifier_label->setPixmap(*pixmap);
    }

    if(index==1) humi_livingroom_capa = 1500;
    if(index==2) humi_livingroom_capa = 1500;
    if(index==3) humi_livingroom_capa = 600;
}

void choose_device::receive_show(){
    if(music_flag==1){
        ui->play_music->show();
        ui->stop_music->hide();
    }else{
        ui->play_music->hide();
        ui->stop_music->show();
    }
    this->show();
}

void choose_device::on_pushButton_clicked()
{
    this->hide();
    emit show_choose_city();
}

bool choose_device::eventFilter(QObject *obj, QEvent *event){
    if (obj==ui->room_air_label || obj==ui->livingroom_air_label) // 指定某个QLabel
    {
        if (event->type() == QEvent::MouseButtonPress) //鼠标点击跳转窗口
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换
            emit show_air();
            return true;

        }
        else
        {
            return false;
        }
    }
    else if (obj==ui->Humidifier_label || obj==ui->livingroom_Humidifier_label) // 指定某个QLabel
    {
        if (event->type() == QEvent::MouseButtonPress) //鼠标点击跳转窗口
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换
            emit show_humi();
            return true;

        }
        else
        {
            return false;
        }
    }

    //    else if(obj==ui->livingroom_air_label){
    //        if (event->type() == QEvent::MouseButtonPress) //鼠标点击跳转窗口
    //        {
    //            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换
    //            emit show_air_livingroom();
    //            return true;
    //        }
    //        else
    //        {
    //            return false;
    //        }
    //    }

    else
    {
        // pass the event on to the parent class
        return QWidget::eventFilter(obj, event);
    }
}

void choose_device::on_return_button_clicked()
{
    this->hide();
    emit return_page();
}

void choose_device::on_play_music_clicked()
{
    ui->play_music->hide();
    ui->stop_music->show();
    music_flag=0;
    emit stop_music();
}

void choose_device::on_stop_music_clicked()
{
    ui->play_music->show();
    ui->stop_music->hide();
    music_flag = 1;
    emit play_music();
}
