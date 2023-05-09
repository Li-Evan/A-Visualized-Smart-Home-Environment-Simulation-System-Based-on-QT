#ifndef CHOOSE_DEVICE_H
#define CHOOSE_DEVICE_H

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
#include <QEvent>
#include <vector>
#include <string>
#include <map>
namespace Ui {
class choose_device;
}

class choose_device : public QWidget
{
    Q_OBJECT

public:
    explicit choose_device(QWidget *parent = 0);
    ~choose_device();

    void paintEvent(QPaintEvent *event);

    bool eventFilter(QObject *obj, QEvent *event);

private slots:

    void on_air_comboBox_currentIndexChanged(int index);

    void on_air_comboBox_2_currentIndexChanged(int index);

    void on_air_comboBox_4_currentIndexChanged(int index);

    void on_air_comboBox_3_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void receive_show();

    void on_air_comboBox_5_currentIndexChanged(int index);

    void on_air_comboBox_6_currentIndexChanged(int index);

    void on_return_button_clicked();

    void on_play_music_clicked();

    void on_stop_music_clicked();

signals:
    void show_choose_city();

    void show_air();
    void show_humi();
    void show_new_wind();

    void return_page();

    void play_music();
    void stop_music();
private:
    Ui::choose_device *ui;
};

#endif // CHOOSE_DEVICE_H
