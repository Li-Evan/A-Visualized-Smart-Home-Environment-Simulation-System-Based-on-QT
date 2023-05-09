#include "myshadowwidget.h"
#include "ui_myshadowwidget.h"
#include <qmath.h>
#include <QGraphicsBlurEffect>

#define SHADOW_WIDTH 10		// 阴影边框宽度;

myshadowwidget::myshadowwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myshadowwidget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
}



void myshadowwidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH), QBrush(Qt::white));

    QColor color(50, 50, 50, 30);
    for (int i = 0; i < SHADOW_WIDTH; i++)
    {

        color.setAlpha(120 - qSqrt(i) * 40);
        painter.setPen(color);
        // 方角阴影边框;
     //   painter.drawRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2);
        // 圆角阴影边框;
        painter.drawRoundedRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2, 4, 4);
    }
}


myshadowwidget::~myshadowwidget()
{
    delete ui;
}
