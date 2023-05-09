#ifndef SELECT_INFO_H
#define SELECT_INFO_H

#include <QWidget>

namespace Ui {
class select_info;
}

class select_info : public QWidget
{
    Q_OBJECT

public:
    explicit select_info(QWidget *parent = 0);
    ~select_info();

private:
    Ui::select_info *ui;
};

#endif // SELECT_INFO_H
