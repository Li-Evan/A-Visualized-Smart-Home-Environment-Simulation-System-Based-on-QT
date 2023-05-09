#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QEvent>
#include <QPainter>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT


signals:
    void show_register();

    void show_start_page();

    void stop_music();
    void play_music();
private slots:
    void receive_show();

    void on_pushbutton_login_clicked();

    void on_pushbutton_register_clicked();

    void on_username_textEdited(const QString &arg1);

    void on_password_textEdited(const QString &arg1);

    void on_play_music_clicked();

    void on_stop_music_clicked();

public:
    explicit login(QWidget *parent = 0);
    ~login();
    void register_account(QString username,QString password);

    void read_user();

    void paintEvent(QPaintEvent *event);


private:
    Ui::login *ui;
};


#endif // LOGIN_H
