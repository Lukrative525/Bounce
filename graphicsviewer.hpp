#ifndef GRAPHICSVIEWER_HPP
#define GRAPHICSVIEWER_HPP

#include <QOpenGLExtraFunctions>
#include <QOpenGLWidget>
#include "camera.hpp"
#include "extrema.hpp"

class Ball;
class MainWindow;

class GraphicsViewer: public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit GraphicsViewer(QWidget* parent = nullptr);
    void refresh_ball_positions(const std::vector<Ball>& ballCollection, const Ball& container);
    void initialize_camera(Ball container);

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
    void set_viewer_extents(Ball container);
    QString read_shader_source(QString filepath);

    Extrema viewerExtents;
    GLuint ballCollectionSize{0};
    GLuint shaderProgram{0};
    GLuint vertexArray{0};
    GLuint vertexBuffer{0};
    GLuint elementBuffer{0};
    GLuint instancePositionBuffer{0};
    GLuint instanceScaleBuffer{0};
    GLuint textureBuffer{0};
    GLuint instanceColorBuffer{0};
    GLint modelViewProjection{0};
    GLint textureMap{0};
    QSize frameSize{0, 0};
    float imageExpansionRatio;
    float borderWidthAsFraction;
};

#endif // GRAPHICSVIEWER_HPP
