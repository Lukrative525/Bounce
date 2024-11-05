#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
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
    void testFunction();

private:
    Ui::MainWindowForm* mainWindowUI;
    GraphicsViewer* graphicsViewer;
};

#endif // MAINWINDOW_HPP
