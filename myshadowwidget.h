#ifndef MYSHADOWWIDGET_H
#define MYSHADOWWIDGET_H

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
class myshadowwidget;
}

class myshadowwidget : public QWidget
{
    Q_OBJECT

public:
    explicit myshadowwidget(QWidget *parent = 0);

    void paintEvent(QPaintEvent *event);
    ~myshadowwidget();

private:
    Ui::myshadowwidget *ui;
};

#endif // MYSHADOWWIDGET_H
