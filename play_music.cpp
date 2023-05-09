#include "play_music.h"
#include "ui_play_music.h"

play_music::play_music(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::play_music)
{
    ui->setupUi(this);
    sound = new QSound(":/音乐/music/Kiss Me More.wav",this);
    sound->setLoops(-1);
    sound->play();
}

play_music::~play_music()
{
    delete ui;
}

void play_music::receive_play_music(){
    sound->play();
}

void play_music::receive_stop_music(){
    sound->stop();
}
