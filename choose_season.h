#ifndef CHOOSE_SEASON_H
#define CHOOSE_SEASON_H

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
#include <QString>
#include <QDebug>
#include <QPainter>
#include "frmsmoothcurve.h"
#include "function.h"
#include <vector>

namespace Ui {
class choose_season;
}

class choose_season : public QWidget
{
    Q_OBJECT

public:
    explicit choose_season(QWidget *parent = 0);
    ~choose_season();

    void paintEvent(QPaintEvent *event);

    bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void receive_show();

//    void on_return_button_clicked();

    void on_play_music_clicked();

    void on_stop_music_clicked();

signals:
    void show_smoothcurve();

    void play_music();
    void stop_music();
//    void return_page();

private:
    Ui::choose_season *ui;
//    frmSmoothCurve w_frmsmoothcurve;
};

#endif // CHOOSE_SEASON_H
