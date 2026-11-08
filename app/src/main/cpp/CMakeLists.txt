cmake_minimum_required(VERSION 3.22.1)

project(neonpanel)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../vendor/imgui-1.90.6)

add_library(neonpanel SHARED
    native.cpp

    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp

    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(neonpanel PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_compile_definitions(neonpanel PRIVATE
    IMGUI_IMPL_OPENGL_ES3
)

find_library(GLES3_LIBRARY GLESv3)
find_library(LOG_LIBRARY log)

target_link_libraries(neonpanel
    ${GLES3_LIBRARY}
    ${LOG_LIBRARY}
)
