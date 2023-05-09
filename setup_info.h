#ifndef SETUP_INFO_H
#define SETUP_INFO_H

#include <QWidget>

namespace Ui {
class setup_info;
}

class setup_info : public QWidget
{
    Q_OBJECT

public:
    explicit setup_info(QWidget *parent = 0);
    ~setup_info();

private:
    Ui::setup_info *ui;
};

#endif // SETUP_INFO_H
