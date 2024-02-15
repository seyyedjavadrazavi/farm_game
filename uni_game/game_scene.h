#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <QDialog>

namespace Ui {
class game_scene;
}

class game_scene : public QDialog
{
    Q_OBJECT

public:
    explicit game_scene(QWidget *parent = nullptr);
    ~game_scene();

private:
    Ui::game_scene *ui;
};

#endif // GAME_SCENE_H
