cmake_minimum_required(VERSION 3.19)
project(Resin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

# Qt Advanced Docking System
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/Qt-Advanced-Docking-System)

qt_add_executable(Resin
    WIN32 MACOSX_BUNDLE

    # Main
    src/main.cpp

    # GUI / Core
    src/core/mainwindow.cpp

    # Rendering
    src/rendering/glwidget.cpp
    src/rendering/shaderclass.cpp
    include/resin/rendering/vbo.h
    include/resin/rendering/vao.h
    include/resin/rendering/ebo.h
    src/rendering/vbo.cpp
    src/rendering/ebo.cpp
    src/rendering/vao.cpp
    include/stb/stb_image.h

    # Headers
    include/resin/core/mainwindow.h
    include/resin/rendering/glwidget.h
    include/resin/rendering/shaderclass.h

    # UI
    ui/mainwindow.ui

    #shaders + textures
    resources/shaders/default.frag
    resources/shaders/default.vert
    resources/shaders/light.frag
    resources/shaders/light.vert
    src/rendering/stb.cpp
    include/resin/rendering/texture.h
    src/rendering/texture.cpp
    include/resin/rendering/camera.h
    src/rendering/camera.cpp
)

target_link_libraries(Resin
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::OpenGL
        Qt::OpenGLWidgets
        OpenGL::GL
        ads::qtadvanceddocking
)

target_include_directories(Resin PRIVATE
    include
    ui
)

target_compile_definitions(Resin PRIVATE
    SHADER_DIR="${CMAKE_SOURCE_DIR}/resources/shaders"
    TEXTURE_DIR="${CMAKE_SOURCE_DIR}/resources/textures"
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
