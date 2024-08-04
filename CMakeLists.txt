cmake_minimum_required(VERSION 3.12)

project(HLViewer VERSION "0.1.0")

include(cmake/get_cpm.cmake)
include(cmake/Dependencies.cmake)

find_package(OpenGL REQUIRED)

add_executable(HLViewer
    README.md
    Common/common.cpp
    Common/common.h
    Common/string.cpp
    Common/string.h
    Common/stringlist.cpp
    basefile.cpp
    basefile.h
    bspfile.cpp
    bspfile.h
    button.cpp
    button.h
    containerfile.h
    containerview.cpp
    containerview.h
    control.cpp
    control.h
    dialog.cpp
    dialog.h
    error.cpp
    error.h
    glad.c
    glcontrol.cpp
    glcontrol.h
    label.cpp
    label.h
    listview.cpp
    listview.h
    listviewitem.cpp
    main.cpp
    main.h
    mdlfile.cpp
    mdlfile.h
    miptexbasedfile.cpp
    miptexbasedfile.h
    program.cpp
    resource.h
    texturecontainer.h
    texturedialog.cpp
    texturedialog.h
    textureview.cpp
    textureview.h
    treeview.cpp
    treeview.h
    treeviewitem.cpp
    wadfile.cpp
    wadfile.h
    window.cpp
    window.h
    wnd.cpp
    wnd.h
)

target_compile_features(HLViewer
    PRIVATE
        cxx_nullptr
        cxx_std_17  # EnTT needs this
)

target_include_directories(HLViewer
    PRIVATE
        "include"
        "."
        "${PROJECT_BINARY_DIR}"
)

target_link_libraries(HLViewer
    PRIVATE
        Comctl32
        glm
        ${OPENGL_LIBRARIES}
)

