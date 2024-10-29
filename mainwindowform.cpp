#include "mainwindowform.hpp"
#include "ui_mainwindowform.h"

MainWindowForm::MainWindowForm(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindowForm)
{
    ui->setupUi(this);
}

MainWindowForm::~MainWindowForm()
{
    delete ui;
}
