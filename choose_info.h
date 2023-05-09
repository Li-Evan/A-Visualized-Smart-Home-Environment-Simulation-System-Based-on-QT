#ifndef SET_INFO_H
#define SET_INFO_H

#include <QWidget>
#include <QEvent>
#include <QPainter>
#include <QPixmap>
#include <QLabel>

namespace Ui {
class choose_info;
}

class choose_info : public QWidget
{
    Q_OBJECT

public:
    explicit choose_info(QWidget *parent = 0);

    void paintEvent(QPaintEvent *event);


    ~choose_info();

signals:
    void show_choose_device();

    void play_music();
    void stop_music();

private slots:

    void receive_show();

    void on_tot_area_textChanged(const QString &arg1);

    void on_room_num_currentTextChanged(const QString &arg1);

    void on_room_area_textChanged(const QString &arg1);

    void on_livingroom_area_textChanged(const QString &arg1);

    void on_window_num_textChanged(const QString &arg1);

    void on_wall_thickness_textChanged(const QString &arg1);

    void on_material_id_currentIndexChanged(int index);

    void on_oriention_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_oriention_currentIndexChanged(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_stop_button_clicked();

private:
    Ui::choose_info *ui;

};

#endif // SET_INFO_H
