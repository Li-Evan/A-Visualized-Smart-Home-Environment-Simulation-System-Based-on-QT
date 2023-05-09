#ifndef PLAY_MUSIC_H
#define PLAY_MUSIC_H

#include <QMainWindow>
#include <QSound>

namespace Ui {
class play_music;
}

class play_music : public QMainWindow
{
    Q_OBJECT

private slots:
    void receive_play_music();

    void receive_stop_music();

public:
    explicit play_music(QWidget *parent = 0);
    ~play_music();

private:
    Ui::play_music *ui;
    QSound* sound;
};

#endif // PLAY_MUSIC_H
