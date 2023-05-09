#ifndef CHOOSE_CITY_H
#define CHOOSE_CITY_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QPixmap>
#include <QPalette>
#include <QList>
#include <QDebug>
#include <QPointF>
#include <QPainterPath>
#include <QVector>
#include <QToolTip>
#include <QPainter>
#include <vector>
#include <string>
#include <map>
#include "frmsmoothcurve.h"


namespace Ui {
class choose_city;
}

class choose_city : public QMainWindow
{
    Q_OBJECT

public:
    explicit choose_city(QMainWindow *parent = 0);
    ~choose_city();

    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);

    bool eventFilter(QObject *obj, QEvent *event);


signals:
    void show_choose_season();

    void return_page();

    void play_music();
    void stop_music();
private:
    Ui::choose_city *ui;


    std::map<QString,std::pair<int,int>> auxiliary_map;



    QVector<QLabel*> city_label_list;
    std::vector<std::pair<int,int>> city_label_pos;
    std::vector<QString> city_label_name;



    void init_all_list();

private slots:
    void receive_show();
    void on_return_button_clicked();
    void on_play_music_clicked();
    void on_stop_music_clicked();
};

#endif // CHOOSE_CITY_H
