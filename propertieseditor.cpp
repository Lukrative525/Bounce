#include "ball.hpp"
#include "propertieseditor.hpp"
#include "mainwindow.hpp"

PropertiesEditor::PropertiesEditor(MainWindow* parent):
    QObject(parent)
{
    parentMainWindow = parent;
}

void PropertiesEditor::set_container(Ball* newContainer)
{
    container = newContainer;
}

void PropertiesEditor::set_container_x(double newValue)
{
    container->position.x = newValue;
    parentMainWindow->update(true);
}

void PropertiesEditor::set_container_y(double newValue)
{
    container->position.y = newValue;
    parentMainWindow->update(true);
}

void PropertiesEditor::set_container_z(double newValue)
{
    container->position.z = newValue;
    parentMainWindow->update(true);
}

void PropertiesEditor::set_container_radius(double newRadius)
{
    container->radius = newRadius;
    parentMainWindow->update(true);
}

void PropertiesEditor::set_container_elasticity(double newElasticity)
{
    container->elasticity = newElasticity;
    parentMainWindow->update(false);
}

void PropertiesEditor::set_selected_ball(Ball* newSelectedBall)
{
    selectedBall = newSelectedBall;
}

void PropertiesEditor::set_ball_x(double newValue)
{
    if (selectedBall != nullptr)
    {
        selectedBall->position.x = newValue;
        parentMainWindow->update(true);
    }
}

void PropertiesEditor::set_ball_y(double newValue)
{
    if (selectedBall != nullptr)
    {
        selectedBall->position.y = newValue;
        parentMainWindow->update(true);
    }
}

void PropertiesEditor::set_ball_z(double newValue)
{
    if (selectedBall != nullptr)
    {
        selectedBall->position.z = newValue;
        parentMainWindow->update(true);
    }
}

void PropertiesEditor::set_ball_radius(double newRadius)
{
    if (selectedBall != nullptr)
    {
        selectedBall->radius = newRadius;
        parentMainWindow->update(true);
    }
}

void PropertiesEditor::set_ball_elasticity(double newElasticity)
{
    if (selectedBall != nullptr)
    {
        selectedBall->elasticity = newElasticity;
        parentMainWindow->update(false);
    }
}

void PropertiesEditor::set_ball_red_component(int newRed)
{
    if (selectedBall != nullptr)
    {
        selectedBall->color.r = newRed / 255.0;
        parentMainWindow->update(false);
    }
}

void PropertiesEditor::set_ball_green_component(int newGreen)
{
    if (selectedBall != nullptr)
    {
        selectedBall->color.g = newGreen / 255.0;
        parentMainWindow->update(false);
    }
}

void PropertiesEditor::set_ball_blue_component(int newBlue)
{
    if (selectedBall != nullptr)
    {
        selectedBall->color.b = newBlue / 255.0;
        parentMainWindow->update(false);
    }
}

void PropertiesEditor::set_ball_movable(bool isMovable)
{
    if (selectedBall != nullptr)
    {
        selectedBall->isMovable = isMovable;
        selectedBall->velocity.x = 0;
        selectedBall->velocity.y = 0;
        selectedBall->velocity.z = 0;
    }
}
