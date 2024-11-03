#include "graphicsviewer.hpp"
#include "mainwindow.hpp"
#include "ui_mainwindowform.h"

MainWindow::MainWindow(QWidget* parent):
    QMainWindow{parent},
    mainWindowUI{new Ui::MainWindowForm}
{
    mainWindowUI->setupUi(this);
    graphicsViewer = new GraphicsViewer(mainWindowUI->frame);
    mainWindowUI->frameGridLayout->addWidget(graphicsViewer);

    simulation.add_ball();
    simulation.add_ball(10, 10, 0, 0.1);

    update();
}

void MainWindow::update()
{
    graphicsViewer->update_graphics(simulation.ballCollection);
}
