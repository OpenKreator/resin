cmake_minimum_required(VERSION 3.19)
project(Resin LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Core
    Widgets
    OpenGL
    OpenGLWidgets
)

find_package(OpenGL REQUIRED)

qt_standard_project_setup()

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

qt_add_executable(Resin
    WIN32 MACOSX_BUNDLE

    # Source files
    src/main.cpp
    src/mainwindow.cpp
    src/glwidget.cpp

    # Header files
    include/mainwindow.h
    include/glwidget.h

    # UI files
    ui/mainwindow.ui

    # Shader files
    src/shaders/vertex.txt
    src/shaders/fragment.txt
)

target_link_libraries(Resin
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::OpenGL
        Qt::OpenGLWidgets
        OpenGL::GL
)

target_include_directories(Resin PRIVATE
    include
    ui
)

target_compile_definitions(Resin PRIVATE
    SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src/shaders"
)

install(TARGETS Resin
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Resin
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
