#include "setup_info.h"
#include "ui_setup_info.h"

setup_info::setup_info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setup_info)
{
    ui->setupUi(this);
}

setup_info::~setup_info()
{
    delete ui;
}
