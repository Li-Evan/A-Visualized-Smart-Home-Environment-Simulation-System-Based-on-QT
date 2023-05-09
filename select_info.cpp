#include "select_info.h"
#include "ui_select_info.h"

select_info::select_info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::select_info)
{
    ui->setupUi(this);
}

select_info::~select_info()
{
    delete ui;
}
