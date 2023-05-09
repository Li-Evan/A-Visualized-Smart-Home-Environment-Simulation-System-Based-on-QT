#include "choose_season.h"
#include "ui_choose_season.h"
#include "choose_city.h"
#include "function.h"
#include "humidity.h"
extern int music_flag;

extern QString province;
extern int season;
extern map<string,map<int,double>> tot_temperature_map;

choose_season::choose_season(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choose_season)
{
    ui->setupUi(this);

    if(music_flag==1){
        ui->play_music->show();
        ui->stop_music->hide();
    }else{
        ui->play_music->hide();
        ui->stop_music->show();
    }
    // 标签图片
    QString pic_path1 = ":/四季图片/image/春.jpg";
    QString pic_path2 = ":/四季图片/image/夏.jpg";
    QString pic_path3 = ":/四季图片/image/秋.jpg";
    QString pic_path4 = ":/四季图片/image/冬.jpg";
    QPixmap *pixmap1 = new QPixmap(pic_path1);
    QPixmap *pixmap2 = new QPixmap(pic_path2);
    QPixmap *pixmap3 = new QPixmap(pic_path3);
    QPixmap *pixmap4 = new QPixmap(pic_path4);
    pixmap1->scaled(ui->spring->size(), Qt::KeepAspectRatio);
    pixmap2->scaled(ui->summer->size(), Qt::KeepAspectRatio);
    pixmap3->scaled(ui->autumn->size(), Qt::KeepAspectRatio);
    pixmap4->scaled(ui->winter->size(), Qt::KeepAspectRatio);
    ui->spring->setScaledContents(true);
    ui->summer->setScaledContents(true);
    ui->autumn->setScaledContents(true);
    ui->winter->setScaledContents(true);
    ui->spring->setPixmap(*pixmap1);
    ui->summer->setPixmap(*pixmap2);
    ui->autumn->setPixmap(*pixmap3);
    ui->winter->setPixmap(*pixmap4);

    // 标签位置
    ui->spring->setGeometry(375,200,500,300);
    ui->autumn->setGeometry(375,550,500,300);
    ui->summer->setGeometry(925,200,500,300);
    ui->winter->setGeometry(925,550,500,300);

    // 设置父窗口
    ui->spring->setParent(this);
    ui->summer->setParent(this);
    ui->autumn->setParent(this);
    ui->winter->setParent(this);

    // 设置鼠标悬浮显示文案
    ui->spring->setToolTip("春");
    ui->summer->setToolTip("夏");
    ui->autumn->setToolTip("秋");
    ui->winter->setToolTip("冬");
    ui->spring->setStyleSheet("QToolTip{font-size:40px;}");
    ui->summer->setStyleSheet("QToolTip{font-size:40px;}");
    ui->autumn->setStyleSheet("QToolTip{font-size:40px;}");
    ui->winter->setStyleSheet("QToolTip{font-size:40px;}");

    // 安装事件过滤器
    ui->spring->installEventFilter(this);
    ui->summer->installEventFilter(this);
    ui->autumn->installEventFilter(this);
    ui->winter->installEventFilter(this);

}


void choose_season::receive_show(){
    if(music_flag==1){
        ui->play_music->show();
        ui->stop_music->hide();
    }else{
        ui->play_music->hide();
        ui->stop_music->show();
    }
    this->show();
}


void choose_season::paintEvent(QPaintEvent *event){
    QPainter p(this); //创建画家，指定窗口为绘图设备
    p.setOpacity(0.4);
    p.drawPixmap(rect(), QPixmap(":/背景图及logo/开始页面"));
}

bool choose_season::eventFilter(QObject *obj, QEvent *event)
{

    bool signal=false;
    int num = 0;
    if(obj==ui->spring){
        signal = true;
        num=1;
    }else if(obj==ui->summer){
        signal = true;
        num=2;
    }else if(obj==ui->autumn){
        signal = true;
        num=3;
    }else if(obj==ui->winter){
        signal = true;
        num=4;
    }
    if (signal) // 选中了季节标签
    {
        if (event->type() == QEvent::MouseButtonPress) // 鼠标点击
        {
            season = num;
            vector<double> temp;
            // 生成温度
            temp = generate_all();
            // 生成湿度
            generate_oneday_basic_humidity();
            // 生成空气质量
            generate_oneday_air_equality();
            this->hide();
            emit show_smoothcurve();
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


choose_season::~choose_season()
{
    delete ui;
}

//void choose_season::on_return_button_clicked()
//{
//    this->hide();
//    emit return_page();
//}

void choose_season::on_play_music_clicked()
{
    ui->play_music->hide();
    ui->stop_music->show();
    music_flag=0;
    emit stop_music();
}

void choose_season::on_stop_music_clicked()
{
    ui->play_music->show();
    ui->stop_music->hide();
    music_flag = 1;
    emit play_music();
}
