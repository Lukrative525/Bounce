#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "simulation.hpp"
class GraphicsViewer;

namespace Ui
{
class MainWindowForm;
}

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    Ui::MainWindowForm* mainWindowUI;
    GraphicsViewer* graphicsViewer;
    Simulation simulation;
};

#endif // MAINWINDOW_HPP
