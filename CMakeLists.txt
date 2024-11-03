cmake_minimum_required(VERSION 3.23)
project(Bounce LANGUAGES CXX VERSION 0.1.0)

FIND_PACKAGE(Qt6 REQUIRED COMPONENTS GUI Widgets OpenGL OpenGLWidgets)
FIND_PACKAGE(glm REQUIRED)
FIND_PACKAGE(GTest REQUIRED)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

# Physics Library
add_library(PhysicsLibrary STATIC)
target_sources(PhysicsLibrary
    PRIVATE
        ball.cpp
        camera.cpp
        physicsfunctions.cpp
        vector3d.cpp
        simulation.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}
        FILES
            ball.hpp
            camera.hpp
            physicsfunctions.hpp
            vector3d.hpp
            simulation.hpp
)
target_compile_features(PhysicsLibrary PUBLIC cxx_std_17)
target_include_directories(PhysicsLibrary PRIVATE)
target_link_libraries(PhysicsLibrary
    PRIVATE
        glm::glm
        Qt6::Core
)

# Physics Library Unit Tests
add_executable(PhysicsLibraryUnitTests)
target_sources(PhysicsLibraryUnitTests
    PRIVATE
        physicslibrary_unittests.cpp
        vector3d_unittests.cpp
        camera_unittests.cpp
)
target_compile_features(PhysicsLibraryUnitTests PUBLIC cxx_std_17)
target_link_libraries(PhysicsLibraryUnitTests
    PRIVATE
        glm::glm
        GTest::GTest
        GTest::Main
        Qt6::Core
        PhysicsLibrary
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
        resources.rc
)
target_compile_features(Bounce PUBLIC cxx_std_17)
target_include_directories(Bounce PRIVATE)
target_link_libraries(Bounce
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
        Qt6::OpenGL
        Qt::OpenGLWidgets
        glm::glm
        PhysicsLibrary
)
