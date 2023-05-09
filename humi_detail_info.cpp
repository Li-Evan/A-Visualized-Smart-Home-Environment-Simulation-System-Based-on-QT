#include "humi_detail_info.h"
#include "ui_humi_detail_info.h"

humi_detail_info::humi_detail_info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::humi_detail_info)
{
    ui->setupUi(this);
}

humi_detail_info::~humi_detail_info()
{
    delete ui;
}

void humi_detail_info::receive_show(){
    this->show();
}
