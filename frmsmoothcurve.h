#ifndef FRMSMOOTHCURVE_H
#define FRMSMOOTHCURVE_H

#include <QWidget>
#include <QList>
#include <QPointF>
#include <QPainterPath>
#include <QLabel>
#include "function.h"

namespace Ui {
class frmSmoothCurve;
}

class frmSmoothCurve : public QWidget
{
    Q_OBJECT

public:
    explicit frmSmoothCurve(QWidget *parent = 0);
    ~frmSmoothCurve();

    bool eventFilter(QObject *watched, QEvent *event);


protected:
    void paintEvent(QPaintEvent *event);

signals:
    void show_lcd();

    void play_music();
    void stop_music();
//    void return_page();

private slots:
    void receive_show();


//    void on_return_button_clicked();

    void on_play_music_clicked();

    void on_stop_music_clicked();

private:
    Ui::frmSmoothCurve *ui;
    QVector<QPointF> datas;     //曲线上的点
    QPainterPath pathNormal;    //正常曲线
    QPainterPath pathSmooth1;   //平滑曲线1
    QPainterPath pathSmooth2;   //平滑曲线2

    // 24个标签
    QList<QLabel*> hours_label_list;
};

#endif // FRMSMOOTHCURVE_H
