#ifndef AIR_DETAIL_INFO_H
#define AIR_DETAIL_INFO_H

#include <QWidget>
#include <QEvent>

namespace Ui {
class air_detail_info;
}

class air_detail_info : public QWidget
{
    Q_OBJECT

public:
    explicit air_detail_info(QWidget *parent = 0);
    ~air_detail_info();

    void paintEvent(QPaintEvent *event);

private slots:
    void receive_show();

private:
    Ui::air_detail_info *ui;
};

#endif // AIR_DETAIL_INFO_H
