cmake_minimum_required(VERSION 3.23)
project(Bounce LANGUAGES CXX VERSION 0.1.0)

FIND_PACKAGE(Qt6 REQUIRED COMPONENTS GUI Widgets OpenGL OpenGLWidgets)
FIND_PACKAGE(glm REQUIRED)
FIND_PACKAGE(GTest REQUIRED)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

# Bounce Library
add_library(BounceLibrary STATIC)
target_sources(BounceLibrary
    PRIVATE
        ball.cpp
        camera.cpp
        extrema.cpp
        jsonreadwritefunctions.cpp
        link.cpp
        physicsfunctions.cpp
        simulation.cpp
        vector3d.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}
        FILES
            ball.hpp
            camera.hpp
            extrema.hpp
            isaveableobject.hpp
            jsonreadwritefunctions.hpp
            link.hpp
            physicsfunctions.hpp
            simulation.hpp
            vector3d.hpp
)
target_compile_features(BounceLibrary PUBLIC cxx_std_17)
target_include_directories(BounceLibrary PRIVATE)
target_link_libraries(BounceLibrary
    PRIVATE
        glm::glm
        Qt6::Core
)

# Physics Library Unit Tests
add_executable(UnitTests)
target_sources(UnitTests
    PRIVATE
        physicsfunctions_unittests.cpp
        vector3d_unittests.cpp
        camera_unittests.cpp
)
target_compile_features(UnitTests PUBLIC cxx_std_17)
target_link_libraries(UnitTests
    PRIVATE
        glm::glm
        GTest::GTest
        GTest::Main
        Qt6::Core
        BounceLibrary
)

# Bounce Application
add_executable(Bounce)
target_sources(Bounce
    PRIVATE
        graphicsviewer.cpp
        graphicsviewer.hpp
        main.cpp
        mainwindow.cpp
        mainwindow.hpp
        mainwindowform.ui
        propertieseditor.cpp
        propertieseditor.hpp
        resources.rc
        shaders.qrc
)
target_compile_features(Bounce PUBLIC cxx_std_17)
target_include_directories(Bounce PRIVATE)
target_link_libraries(Bounce
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
        Qt6::OpenGL
        Qt6::OpenGLWidgets
        glm::glm
        BounceLibrary
)
