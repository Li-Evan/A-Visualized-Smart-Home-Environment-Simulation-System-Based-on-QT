#ifndef TO_REGISTER_H
#define TO_REGISTER_H

#include <QWidget>
#include <QEvent>
#include <QPainter>

namespace Ui {
class to_register;
}

class to_register : public QWidget
{
    Q_OBJECT
signals:
    void show_login();

    void play_music();
    void stop_music();

//    void show_begin_page();
private slots:

    void receive_show();


    void on_username_textChanged(const QString &arg1);

    void on_password_textChanged(const QString &arg1);

    void on_pushbutton_login_clicked();

    void on_pushbutton_register_clicked();

    void on_play_music_clicked();

    void on_stop_music_clicked();

public:
    explicit to_register(QWidget *parent = 0);
    ~to_register();

    void paintEvent(QPaintEvent *event);

    void register_account();
    void read_test();

private:
    Ui::to_register *ui;
};

#endif // TO_REGISTER_H
