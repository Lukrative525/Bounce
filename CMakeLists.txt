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
add_library(PhysicsLibrary STATIC
    simulation.hpp simulation.cpp)
target_sources(PhysicsLibrary
    PRIVATE
        physicsfunctions.cpp
        vector3d.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}
        FILES
            physicsfunctions.hpp
            vector3d.hpp
)
target_compile_features(PhysicsLibrary PUBLIC cxx_std_17)
target_include_directories(PhysicsLibrary PRIVATE)

# Physics Library Unit Tests
add_executable(PhysicsLibraryUnitTests)
target_sources(PhysicsLibraryUnitTests
    PRIVATE
        physicslibrary_unittests.cpp
        vector3d_unittests.cpp
)
target_compile_features(PhysicsLibraryUnitTests PUBLIC cxx_std_17)
target_link_libraries(PhysicsLibraryUnitTests
    PRIVATE
    GTest::GTest
    GTest::Main
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
        physicsfunctions.cpp
        physicsfunctions.hpp
        resources.rc
        vector3d.cpp
        vector3d.hpp
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
