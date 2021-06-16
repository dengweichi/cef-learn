cmake_minimum_required(VERSION 3.7)

project(cef_learn)



set(CMAKE_CXX_STANDARD 14)


include_directories(./cef)
include_directories(./cef/include)

add_executable( ${PROJECT_NAME} WIN32
        ./src/cefsimple_win.cc
        ./src/resource.h
        ./src/simple_app.cc
        ./src/simple_app.h
        ./src/simple_handler.h
        ./src/simple_handler.cc
        ./src/simple_handler_win.cc
        )

# 设置windows系统下需要链接的静态库
set(WINDOW_LINK_LIB shell32.lib kernel32.lib user32.lib ole32.lib oleaut32.lib gdi32.lib)

# 环境的配置
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries( ${PROJECT_NAME}  ${WINDOW_LINK_LIB}  ${PROJECT_SOURCE_DIR}/cef/lib/release/libcef.lib ${PROJECT_SOURCE_DIR}/cef/lib/release/libcef_dll_wrapper.lib)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries( ${PROJECT_NAME}  ${WINDOW_LINK_LIB}  ${PROJECT_SOURCE_DIR}/cef/lib/debug/libcef.lib ${PROJECT_SOURCE_DIR}/cef/lib/debug/libcef_dll_wrapper.lib)
else()
    message(STATUS "只支持 Release/Debug")
endif()




# 链接 mainfest文件
target_link_libraries(${PROJECT_NAME} -manifest:embed -manifestinput:"${PROJECT_SOURCE_DIR}/cef_learn.exe.manifest")

# 复制cef所需的运行库
file(COPY ./cef/dep/ DESTINATION ${CMAKE_BINARY_DIR})