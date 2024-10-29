#include "mainwindow.hpp"
#include "ui_mainwindowform.h"

MainWindow::MainWindow(QWidget* parent)
    :QMainWindow{parent}, mainWindowUI{new Ui::MainWindowForm}
{
    mainWindowUI->setupUi(this);
}
