#ifndef GRAPHICSVIEWER_HPP
#define GRAPHICSVIEWER_HPP

#include <array>
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
    void initialize_camera(const Ball& container);

    Camera camera;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    glm::vec3 convert_screen_to_world(const QPointF& screen_coordinates);
    glm::vec2 convert_screen_to_normalized(const glm::vec2& screen_coordinates);
    glm::vec3 convert_normalized_to_world(const glm::vec2& normalized_coordinates);

private:
    void initialize_shader_program();
    void initialize_texture();
    void initialize_vertex_array(GLuint& vertexArray);
    void initialize_vertex_attribute_array(GLuint layout_location, GLuint length, GLuint stride, GLuint offset);
    void initialize_instance_attribute_array(GLuint& instancePropertyBuffer, GLuint layout_location, GLuint length, GLuint stride, GLuint offset);
    void unbind_all_buffers_and_vertex_arrays();
    void load_vertex_data_into_vertex_buffer(GLuint& vertexBuffer);
    void load_vertex_indices_into_element_buffer(GLuint& elementBuffer);
    void verify_shader_compilation(const GLuint& objectToVerify);
    void verify_program_linking(const GLuint& objectToVerify);
    void set_viewer_extents(const Ball& container);
    QString read_shader_source(const QString& filepath);

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
    GLint modelViewProjectionAddress{0};
    glm::mat4x4 modelViewProjectionMatrix{0};
    GLint textureMap{0};
    QSize frameSize{0, 0};
    float imageExpansionRatio;
    float borderWidthAsFraction;
    const std::array<float, 20> boxVertices;
    const std::array<GLuint, 6> vertexIndices;
    QPointF mousePressPosition;
    QPointF mouseCurrentPosition;
    bool mousePressed{false};
    bool mouseMoved{false};
};

#endif // GRAPHICSVIEWER_HPP
