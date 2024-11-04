#ifndef GRAPHICSVIEWER_HPP
#define GRAPHICSVIEWER_HPP

#include <QOpenGLExtraFunctions>
#include <QOpenGLWidget>
#include <vector>
#include "ball.hpp"
#include "camera.hpp"

class GraphicsViewer: public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit GraphicsViewer(QWidget* parent = nullptr);
    void update_object_positions(const std::vector<Ball>& ballCollection);
    QString read_shader_source(QString filepath);
    Camera camera;
protected:
    void initializeGL() override;
    void paintGL() override;
    void verify_shader_compilation(GLuint& objectToVerify);
    void verify_program_linking(GLuint& objectToVerify);
    GLuint shaderProgram{0};
    GLuint vertexArrayObject{0};
    GLuint vertexBufferObject{0};
    GLuint elementBufferObject{0};
    GLuint instanceVertexBufferObject{0};
};

#endif // GRAPHICSVIEWER_HPP
