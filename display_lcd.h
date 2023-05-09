#ifndef DISPLAY_LCD_H
#define DISPLAY_LCD_H

#include <QWidget>
#include <QEvent>
#include <QVector>

namespace Ui {
class Display_LCD;
}

class Display_LCD : public QWidget
{
    Q_OBJECT

public:
    explicit Display_LCD(QWidget *parent = 0);
    ~Display_LCD();

    // 计时器事件
    void timerEvent(QTimerEvent *event);

    // 画图事件
    void paintEvent(QPaintEvent *event);

signals:
    void show_bingtu();
    void play_music();
    void stop_music();

private slots:
    void receive_show();

    void on_pushButton_clicked();

    void on_play_music_clicked();

    void on_stop_music_clicked();

private:
    Ui::Display_LCD *ui;
    int lcd_timer;

    void generate_all_change();
    void generate_all_humidity_change();
    void generate_all_equality_change();

};

#endif // DISPLAY_LCD_H
