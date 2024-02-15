#include "game_scene.h"
#include "ui_game_scene.h"

game_scene::game_scene(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game_scene)
{
    ui->setupUi(this);
}

game_scene::~game_scene()
{
    delete ui;
}
