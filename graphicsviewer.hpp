#ifndef GRAPHICSVIEWER_HPP
#define GRAPHICSVIEWER_HPP

#include <QOpenGLWidget>

class GraphicsViewer : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GraphicsViewer(QWidget* parent = nullptr);
};

#endif // GRAPHICSVIEWER_H
