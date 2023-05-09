#ifndef START_PAGE_H
#define START_PAGE_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QPixmap>
#include <QPalette>
#include <QList>
#include <QPointF>
#include <QPainterPath>
#include <QVector>
#include <QToolTip>
#include <QPainter>

namespace Ui {
class start_page;
}

class start_page : public QWidget
{
    Q_OBJECT

public:
    explicit start_page(QWidget *parent = 0);
    ~start_page();

    void paintEvent(QPaintEvent *event);

signals:
    void show_choose_info();
    void play_music();
    void stop_music();

private slots:
    void on_pushButton_clicked();

    void receive_show();

    void on_play_music_clicked();

    void on_stop_music_clicked();

private:
    Ui::start_page *ui;
};

#endif // START_PAGE_H
