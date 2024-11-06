#ifndef GRAPHICSVIEWER_HPP
#define GRAPHICSVIEWER_HPP

#include <QOpenGLExtraFunctions>
#include <QOpenGLWidget>
#include "camera.hpp"


class Ball;
class MainWindow;

class GraphicsViewer: public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit GraphicsViewer(QWidget* parent = nullptr);
    void refresh_ball_positions(std::vector<Ball> ballCollection);
    Camera camera;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

private:
    void initialize_shader_program();
    void initialize_texture();
    void verify_shader_compilation(GLuint& objectToVerify);
    void verify_program_linking(GLuint& objectToVerify);
    QString read_shader_source(QString filepath);
    GLuint ballCollectionSize{0};
    GLuint shaderProgram{0};
    GLuint vertexArray{0};
    GLuint vertexBuffer{0};
    GLuint elementBuffer{0};
    GLuint instanceVertexBuffer{0};
    GLuint instanceScaleBuffer;
    GLuint textureBuffer;
    GLint projection{0};
    GLint view{0};
    GLint textureMap{0};
    QSize frameSize{0, 0};
};

#endif // GRAPHICSVIEWER_HPP
