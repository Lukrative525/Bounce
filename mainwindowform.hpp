#ifndef MAINWINDOWFORM_HPP
#define MAINWINDOWFORM_HPP

#include <QMainWindow>

namespace Ui
{
class MainWindowForm;
}

class MainWindowForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowForm(QWidget *parent = nullptr);
    ~MainWindowForm();

private:
    Ui::MainWindowForm* ui;
};

#endif // MAINWINDOWFORM_HPP
