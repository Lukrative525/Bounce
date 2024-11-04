#include <glm/gtc/type_ptr.hpp>
#include <QFile>
#include "ball.hpp"
#include "graphicsviewer.hpp"

GraphicsViewer::GraphicsViewer(QWidget *parent):
    QOpenGLWidget{parent} {}

void GraphicsViewer::initializeGL()
{
    this->makeCurrent();

    float boxVertices[] =
    {
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };

    GLuint vertexIndices[] =
    {
        0, 1, 2,
        0, 3, 2
    };

    QString vertexSource = read_shader_source(":/shaders/vertex_shader.vert");
    QString fragmentSource = read_shader_source(":/shaders/fragment_shader.frag");
    QByteArray vertexSourceUtf8 = vertexSource.toUtf8();
    QByteArray fragmentSourceUtf8 = fragmentSource.toUtf8();
    const char* vertexSourceChar = vertexSourceUtf8.data();
    const char* fragmentSourceChar = fragmentSourceUtf8.data();

    initializeOpenGLFunctions();

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

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glGenBuffers(1, &instanceVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVertexBufferObject);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glVertexAttribDivisor(1, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GraphicsViewer::paintGL()
{
    this->makeCurrent();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);

    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");

    camera.regenerate_projection_matrix();
    camera.regenerate_view_matrix();
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera.projectionMatrix));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.viewMatrix));

    glBindVertexArray(vertexArrayObject);
    // GLsizei instanceCount = ballCollection.size();
    GLsizei instanceCount = 1;
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, instanceCount);

    glBindVertexArray(0);
    glUseProgram(0);
}

void GraphicsViewer::update_object_positions(const std::vector<Ball>& ballCollection)
{
    std::vector<glm::vec3> positions(ballCollection.size());
    for (int i{0}; i < positions.size(); i++)
    {
        positions[i][0] = ballCollection[i].position[0];
        positions[i][1] = ballCollection[i].position[1];
        positions[i][2] = ballCollection[i].position[2];
    }

    // throwing an error here: how do we make sure that this is never run before initializeGL?
    glBindBuffer(GL_ARRAY_BUFFER, instanceVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
