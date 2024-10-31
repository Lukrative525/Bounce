cmake_minimum_required(VERSION 3.23)
project(Bounce LANGUAGES CXX VERSION 0.1.0)

FIND_PACKAGE(Qt6 REQUIRED COMPONENTS GUI Widgets OpenGL OpenGLWidgets)
FIND_PACKAGE(glm REQUIRED)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

add_executable(Bounce)

target_sources(Bounce
    PRIVATE
        main.cpp
        mainwindow.cpp
        mainwindow.hpp
        mainwindowform.ui
        resources.rc
)

target_compile_features(Bounce PUBLIC cxx_std_17)
target_include_directories(Bounce PRIVATE)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Gui
    Qt6::OpenGL
    Qt::OpenGLWidgets
    glm::glm
)
