#ifndef HUMI_DETAIL_INFO_H
#define HUMI_DETAIL_INFO_H

#include <QWidget>

namespace Ui {
class humi_detail_info;
}

class humi_detail_info : public QWidget
{
    Q_OBJECT

public:
    explicit humi_detail_info(QWidget *parent = 0);
    ~humi_detail_info();

private slots:
    void receive_show();

private:
    Ui::humi_detail_info *ui;
};

#endif // HUMI_DETAIL_INFO_H
