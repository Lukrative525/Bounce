#ifndef PROPERTIESEDITOR_H
#define PROPERTIESEDITOR_H

#include <QWidget>
class Ball;
class MainWindow;
class Vector3D;

class PropertiesEditor: public QObject
{
    Q_OBJECT
public:
    explicit PropertiesEditor(MainWindow* parentMainWindow);

public slots:
    void set_gravity(Vector3D* newGravity);
    void set_gravity_x(double newValue);
    void set_gravity_y(double newValue);
    void set_gravity_z(double newValue);
    void set_container(Ball* newContainer);
    void set_container_x(double newValue);
    void set_container_y(double newValue);
    void set_container_z(double newValue);
    void set_container_radius(double newRadius);
    void set_container_elasticity(double newElasticity);
    void set_selected_ball(Ball* newSelectedBall);
    void set_ball_x(double newValue);
    void set_ball_y(double newValue);
    void set_ball_z(double newValue);
    void set_ball_radius(double newRadius);
    void set_ball_elasticity(double newElasticity);
    void set_ball_red_component(int newRed);
    void set_ball_green_component(int newGreen);
    void set_ball_blue_component(int newBlue);
    void set_ball_movable(bool isMovable);

private:
    MainWindow* parentMainWindow;
    Vector3D* gravity;
    Ball* container;
    Ball* selectedBall;
};

#endif // PROPERTIESEDITOR_H
