#include <glm/gtc/type_ptr.hpp>
#include <QFile>
#include <vector>
#include "ball.hpp"
#include "camera.hpp"
#include "extrema.hpp"
#include "graphicsviewer.hpp"

GraphicsViewer::GraphicsViewer(QWidget *parent):
    QOpenGLWidget{parent},
    boxVertices
    {
        1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, -1.0f, 1.0f, 0.0f
    },
    vertexIndices
    {
        0, 1, 2,
        0, 3, 2
    }
{
    float imageWidth{256};
    float imageCircleDiameter{248};
    imageExpansionRatio = imageWidth / imageCircleDiameter;

    borderWidthAsFraction = 0.02;
}

void GraphicsViewer::initializeGL()
{
    initializeOpenGLFunctions();

    initialize_shader_program();
    initialize_texture();

    modelViewProjection = glGetUniformLocation(shaderProgram, "modelViewProjection");
    textureMap = glGetUniformLocation(shaderProgram, "textureMap");

    initialize_vertex_array(vertexArray);

    load_vertex_data_into_vertex_buffer(vertexBuffer);
    load_vertex_indices_into_element_buffer(elementBuffer);

    initialize_vertex_attribute_array(0, 3, 5 * sizeof(float), 0);
    initialize_vertex_attribute_array(1, 2, 5 * sizeof(float), 3 * sizeof(float));

    initialize_instance_attribute_array(instancePositionBuffer, 2, 3, sizeof(glm::vec3), 0);
    initialize_instance_attribute_array(instanceScaleBuffer, 3, 1, sizeof(float), 0);
    initialize_instance_attribute_array(instanceColorBuffer, 4, 4, sizeof(glm::vec4), 0);

    unbind_all_buffers_and_vertex_arrays();
}

void GraphicsViewer::paintGL()
{
    glClearColor(0.0f, 0.18f, 0.36f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(shaderProgram);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureBuffer);
    glUniform1i(textureMap, 0);

    camera.center_camera(frameSize, viewerExtents);
    camera.regenerate_projection_matrix();
    camera.regenerate_view_matrix();
    glUniformMatrix4fv(modelViewProjection, 1, GL_FALSE, glm::value_ptr(camera.get_projection_matrix() * camera.get_view_matrix()));

    glBindVertexArray(vertexArray);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, ballCollectionSize);

    glBindVertexArray(0);
    glUseProgram(0);
}

void GraphicsViewer::resizeGL(int width, int height)
{
    frameSize.setWidth(width);
    frameSize.setHeight(height);
}

void GraphicsViewer::refresh_ball_positions(const std::vector<Ball>& ballCollection, const Ball& container)
{
    ballCollectionSize = ballCollection.size() + 1;
    std::vector<glm::vec3> positions(ballCollectionSize);
    std::vector<float> radii(ballCollectionSize);
    std::vector<glm::vec4> colors(ballCollectionSize);

    positions[0].x = container.position.x;
    positions[0].y = container.position.y;
    positions[0].z = container.position.z;
    radii[0] = imageExpansionRatio * container.radius;
    colors[0] = container.color;

    for (int i{1}; i < ballCollectionSize; i++)
    {
        positions[i].x = ballCollection[i - 1].position.x;
        positions[i].y = ballCollection[i - 1].position.y;
        positions[i].z = ballCollection[i - 1].position.z;
        radii[i] = imageExpansionRatio * ballCollection[i - 1].radius;
        colors[i] = ballCollection[i - 1].color;
    }

    set_viewer_extents(container);

    glBindBuffer(GL_ARRAY_BUFFER, instancePositionBuffer);
    glBufferData(GL_ARRAY_BUFFER, ballCollectionSize * sizeof(glm::vec3), positions.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, instanceScaleBuffer);
    glBufferData(GL_ARRAY_BUFFER, ballCollectionSize * sizeof(float), radii.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, instanceColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, ballCollectionSize * sizeof(glm::vec4), colors.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GraphicsViewer::initialize_camera(const Ball& container)
{
    camera.set_camera_position(container.position.x, container.position.y - container.radius * (1 + borderWidthAsFraction), container.position.z);
    camera.set_camera_target(container.position);
    camera.set_camera_up_direction(0, 0, 1);
    camera.set_near_plane(0);
    camera.set_far_plane(2 * (container.radius * (1 + borderWidthAsFraction)));
}

void GraphicsViewer::initialize_shader_program()
{
    QString vertexSource = read_shader_source(":/shaders/vertex_shader.vert");
    QString fragmentSource = read_shader_source(":/shaders/fragment_shader.frag");
    QByteArray vertexSourceUtf8 = vertexSource.toUtf8();
    QByteArray fragmentSourceUtf8 = fragmentSource.toUtf8();
    const char* vertexSourceChar = vertexSourceUtf8.data();
    const char* fragmentSourceChar = fragmentSourceUtf8.data();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSourceChar, NULL);
    glCompileShader(vertexShader);
    verify_shader_compilation(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSourceChar, NULL);
    glCompileShader(fragmentShader);
    verify_shader_compilation(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    verify_program_linking(shaderProgram);
}

void GraphicsViewer::initialize_texture()
{
    QImage textureImage(":/textures/shaded_circle.png");
    textureImage = textureImage.convertToFormat(QImage::Format_RGBA8888);

    glGenTextures(1, &textureBuffer);
    glBindTexture(GL_TEXTURE_2D, textureBuffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.width(), textureImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.bits());
    glGenerateMipmap(GL_TEXTURE_2D);
}

void GraphicsViewer::initialize_vertex_array(GLuint& vertexArray)
{
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
}

void GraphicsViewer::initialize_vertex_attribute_array(GLuint layout_location, GLuint length, GLuint stride, GLuint offset)
{
    glEnableVertexAttribArray(layout_location);
    glVertexAttribPointer(layout_location, length, GL_FLOAT, GL_FALSE, stride, (void*)(uintptr_t)(offset));
}

void GraphicsViewer::initialize_instance_attribute_array(GLuint& instancePropertyBuffer, GLuint layout_location, GLuint length, GLuint stride, GLuint offset)
{
    glGenBuffers(1, &instancePropertyBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, instancePropertyBuffer);

    initialize_vertex_attribute_array(layout_location, length, stride, offset);
    glVertexAttribDivisor(layout_location, 1);
}

void GraphicsViewer::unbind_all_buffers_and_vertex_arrays()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GraphicsViewer::load_vertex_data_into_vertex_buffer(GLuint& vertexBuffer)
{
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices.data(), GL_STATIC_DRAW);
}

void GraphicsViewer::load_vertex_indices_into_element_buffer(GLuint& elementBuffer)
{
    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices.data(), GL_STATIC_DRAW);
}

void GraphicsViewer::verify_shader_compilation(const GLuint& shaderToVerify)
{
    GLint success;
    char infoLog[512];

    glGetShaderiv(shaderToVerify, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderToVerify, 512, NULL, infoLog);
        qDebug() << "Shader compilation failed:\n" << infoLog;
    }
}

void GraphicsViewer::verify_program_linking(const GLuint& programToVerify)
{
    GLint success;
    char infoLog[512];

    glGetProgramiv(programToVerify, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(programToVerify, 512, NULL, infoLog);
        qDebug() << "Program linking failed:\n" << infoLog;
    }
}

void GraphicsViewer::set_viewer_extents(const Ball& container)
{
    viewerExtents.minimumX = container.position.x - container.radius * (1 + borderWidthAsFraction);
    viewerExtents.maximumX = container.position.x + container.radius * (1 + borderWidthAsFraction);
    viewerExtents.minimumY = container.position.z - container.radius * (1 + borderWidthAsFraction);
    viewerExtents.maximumY = container.position.z + container.radius * (1 + borderWidthAsFraction);
}

QString GraphicsViewer::read_shader_source(const QString& filepath)
{
    QString data;
    QFile file(filepath);

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"file not opened";
    }
    else
    {
        data = file.readAll();
    }

    return data;
}
