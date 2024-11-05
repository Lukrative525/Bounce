#ifndef GRAPHICSVIEWER_HPP
#define GRAPHICSVIEWER_HPP

#include <QOpenGLExtraFunctions>
#include <QOpenGLWidget>
#include "camera.hpp"
#include "simulation.hpp"

class Ball;
class MainWindow;

class GraphicsViewer: public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit GraphicsViewer(QWidget* parent = nullptr);
    void update_ball_positions();
    Camera camera;
    Simulation simulation;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

private:
    void verify_shader_compilation(GLuint& objectToVerify);
    void verify_program_linking(GLuint& objectToVerify);
    QString read_shader_source(QString filepath);
    GLuint ballCollectionSize{0};
    GLuint shaderProgram{0};
    GLuint vertexArrayObject{0};
    GLuint vertexBufferObject{0};
    GLuint elementBufferObject{0};
    GLuint instanceVertexBufferObject{0};
    GLuint projection{0};
    GLuint view{0};
    QSize frameSize{0, 0};
};

#endif // GRAPHICSVIEWER_HPP
