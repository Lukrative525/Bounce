#include <glm/gtc/type_ptr.hpp>
#include <QFile>
#include <vector>
#include "ball.hpp"
#include "camera.hpp"
#include "extrema.hpp"
#include "graphicsviewer.hpp"

GraphicsViewer::GraphicsViewer(QWidget *parent):
    QOpenGLWidget{parent}
{
    float imageWidth{256};
    float imageCircleDiameter{248};
    imageExpansionRatio = imageWidth / imageCircleDiameter;

    borderWidthAsFraction = 0.01;
}

void GraphicsViewer::initializeGL()
{
    float boxVertices[] =
    {
        1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, -1.0f, 1.0f, 0.0f
    };

    GLuint vertexIndices[] =
    {
        0, 1, 2,
        0, 3, 2
    };

    initializeOpenGLFunctions();

    initialize_shader_program();

    initialize_texture();

    modelViewProjection = glGetUniformLocation(shaderProgram, "modelViewProjection");
    textureMap = glGetUniformLocation(shaderProgram, "textureMap");

    // create and bind vertex array
    glGenVertexArrays(1, &vertexArray); // create vertex array and assign its ID to "vertexArray"
    glBindVertexArray(vertexArray); // bind vertex array corresponding to "vertexArray" ID

    // loading vertex data into buffer
    glGenBuffers(1, &vertexBuffer); // create buffer and assign its ID to "vertexBuffer"
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // bind buffer corresponding to "vertexBuffer" ID to GL_ARRAY_BUFFER target
    glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW); // load "boxVertices" data into currently bound buffer

    // loading vertex indices into buffer
    glGenBuffers(1, &elementBuffer); // create buffer and assign its ID to "elementBuffer"
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer); // bind buffer corresponding to "elementBuffer" ID to GL_ELEMENT_ARRAY_BUFFER target
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW); // load "vertexIndices" data into currently bound buffer

    // NOTE: the glVertexAttribPointer function only applies to the buffer last bound to GL_ARRAY_BUFFER target

    // setting up vertex attribute array for the vertex coordinates
    glEnableVertexAttribArray(0); // enable vertex attribute array at layout location 0 (position)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // specify that the position attributes for the vertices are 3 floats long, not normalized, spaced 5 floats worth of bytes apart, and start at the first float in the currently bound buffer

    // setting up vertex attribute array for the texture coordinates
    glEnableVertexAttribArray(1); // enable vertex attribute array at layout location 1 (textureCoordinates)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // specify that the textureCoordinates attributes for the vertices are 2 floats long, not normalized, spaced 5 floats worth of bytes apart, and start at the fourth float in the currently bound buffer

    // setting up a buffer for instance position
    glGenBuffers(1, &instancePositionBuffer); // create buffer and assign its ID to "instancePositionBuffer"
    glBindBuffer(GL_ARRAY_BUFFER, instancePositionBuffer); // bind buffer corresponding to "instancePositionBuffer" ID to GL_ARRAY_BUFFER target

    glEnableVertexAttribArray(2); // enable vertex attribute array at layout location 2 (instancePosition)
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0); // specify that the instancePosition attributes for the vertices are 3 floats long, not normalized, spaced 3 floats worth of bytes apart, and start at the first float in the currently bound buffer
    glVertexAttribDivisor(2, 1);

    // setting up a buffer for instance scale
    glGenBuffers(1, &instanceScaleBuffer); // create buffer and assign its ID to "instanceScaleBuffer"
    glBindBuffer(GL_ARRAY_BUFFER, instanceScaleBuffer); // bind buffer corresponding to "instanceScaleBuffer" ID to GL_ARRAY_BUFFER target

    glEnableVertexAttribArray(3); // enable vertex attribute array at layout location 3 (instanceScale)
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0); // specify that the instanceScale attributes for the vertices are 1 float long, not normalized, spaced 1 float worth of bytes apart, and start at the first float in the currently bound buffer
    glVertexAttribDivisor(3, 1);

    // setting up a buffer for instance color
    glGenBuffers(1, &instanceColorBuffer); // create buffer and assign its ID to "instanceColorBuffer"
    glBindBuffer(GL_ARRAY_BUFFER, instanceColorBuffer); // bind buffer corresponding to "instanceColorBuffer" ID to GL_ARRAY_BUFFER target

    glEnableVertexAttribArray(4); // enable vertex attribute array at layout location 4 (instanceColor)
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0); // specify that the instanceColor attributes for the vertices are 4 floats long, not normalized, spaced 4 floats worth of bytes apart, and start at the first float in the currently bound buffer
    glVertexAttribDivisor(4, 1);

    // unbinding all array buffers and vertex array
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GraphicsViewer::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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

void GraphicsViewer::refresh_ball_positions(std::vector<Ball> ballCollection, Ball container)
{
    ballCollectionSize = ballCollection.size() + 1;
    std::vector<glm::vec3> positions(ballCollectionSize);
    std::vector<float> radii(ballCollectionSize);
    std::vector<glm::vec4> colors(ballCollectionSize);

    positions[0][0] = container.position[0];
    positions[0][1] = container.position[1];
    positions[0][2] = container.position[2];
    radii[0] = imageExpansionRatio * container.radius;
    colors[0] = container.color;

    for (int i{1}; i < ballCollectionSize; i++)
    {
        positions[i][0] = ballCollection[i - 1].position[0];
        positions[i][1] = ballCollection[i - 1].position[1];
        positions[i][2] = ballCollection[i - 1].position[2];
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

void GraphicsViewer::initialize_camera(Ball container)
{
    camera.set_camera_position(container.position[0], container.position[1] - container.radius * (1 + borderWidthAsFraction), container.position[2]);
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

void GraphicsViewer::set_viewer_extents(Ball container)
{
    viewerExtents.minimumX = container.position[0] - container.radius * (1 + borderWidthAsFraction);
    viewerExtents.maximumX = container.position[0] + container.radius * (1 + borderWidthAsFraction);
    viewerExtents.minimumY = container.position[2] - container.radius * (1 + borderWidthAsFraction);
    viewerExtents.maximumY = container.position[2] + container.radius * (1 + borderWidthAsFraction);
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
