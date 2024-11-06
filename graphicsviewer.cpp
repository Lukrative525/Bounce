#include <glm/gtc/type_ptr.hpp>
#include <QFile>
#include <vector>
#include "ball.hpp"
#include "camera.hpp"
#include "graphicsviewer.hpp"

GraphicsViewer::GraphicsViewer(QWidget *parent):
    QOpenGLWidget{parent} {}

void GraphicsViewer::initializeGL()
{
    float boxVertices[] =
    {
        1.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, -1.0f,
        1.0f, 0.0f, -1.0f
    };

    GLuint vertexIndices[] =
    {
        0, 1, 2,
        0, 3, 2
    };

    initializeOpenGLFunctions();

    initialize_shader_program();

    projection = glGetUniformLocation(shaderProgram, "projection");
    view = glGetUniformLocation(shaderProgram, "view");

    // all following code working on vertex array until vertex array unbound
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    // loadingg vertex coordinates into buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);

    // loading vertex indices into element buffer
    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // setting up instance vertex buffer
    glGenBuffers(1, &instanceVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVertexBuffer);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glVertexAttribDivisor(1, 1);

    // setting up instance scale buffer
    glGenBuffers(1, &instanceScaleBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, instanceScaleBuffer);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
    glVertexAttribDivisor(2, 1);

    // unbinding buffers and vertex array
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GraphicsViewer::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    camera.center_camera(frameSize, 0, 0, 10, 10);
    camera.set_camera_target(0, 1, 0);
    camera.set_camera_up_direction(0, 0, 1);
    camera.regenerate_projection_matrix();
    camera.regenerate_view_matrix();
    glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(camera.get_projection_matrix()));
    glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(camera.get_view_matrix()));

    glBindVertexArray(vertexArray);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, ballCollectionSize);

    glBindVertexArray(0);
    glUseProgram(0);
}

void GraphicsViewer::resizeGL(int width, int height)
{
    this->frameSize = QSize(width, height);
}

void GraphicsViewer::refresh_ball_positions(std::vector<Ball> ballCollection)
{
    ballCollectionSize = ballCollection.size();
    std::vector<glm::vec3> positions(ballCollectionSize);
    std::vector<float> radii(ballCollectionSize);
    for (int i{0}; i < positions.size(); i++)
    {
        positions[i][0] = ballCollection[i].position[0];
        positions[i][1] = ballCollection[i].position[1];
        positions[i][2] = ballCollection[i].position[2];
        radii[i] = ballCollection[i].radius;
    }

    glBindBuffer(GL_ARRAY_BUFFER, instanceVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, instanceScaleBuffer);
    glBufferData(GL_ARRAY_BUFFER, radii.size() * sizeof(float), radii.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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

void GraphicsViewer::verify_shader_compilation(GLuint& shaderToVerify)
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

void GraphicsViewer::verify_program_linking(GLuint& programToVerify)
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

QString GraphicsViewer::read_shader_source(QString filepath)
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
