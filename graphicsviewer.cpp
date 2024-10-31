#include "graphicsviewer.hpp"

GraphicsViewer::GraphicsViewer(QWidget *parent):
    QOpenGLWidget{parent}
{

}

void GraphicsViewer::initializeGL()
{
    qDebug() << "we\'re here!";
}
