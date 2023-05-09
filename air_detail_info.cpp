#include "air_detail_info.h"
#include "ui_air_detail_info.h"
#include <QDebug>

air_detail_info::air_detail_info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::air_detail_info)
{
    ui->setupUi(this);
    ui->detail_jingxiang->installEventFilter(this);
}

air_detail_info::~air_detail_info()
{
    delete ui;

}

void air_detail_info::paintEvent(QPaintEvent *event){

}

void air_detail_info::receive_show(){
    this->show();
}
