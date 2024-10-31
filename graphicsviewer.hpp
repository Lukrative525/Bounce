#ifndef GRAPHICSVIEWER_HPP
#define GRAPHICSVIEWER_HPP

#include <QOpenGLExtraFunctions>
#include <QOpenGLWidget>

class GraphicsViewer: public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit GraphicsViewer(QWidget* parent = nullptr);

protected:
    void initializeGL() override;
    void paintGL() override;
    GLuint shaderProgram{0};
    GLuint vertexBufferObject{0};
    GLuint vertexArrayObject{0};
};

#endif // GRAPHICSVIEWER_HPP
