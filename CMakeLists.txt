cmake_minimum_required(VERSION 3.10)
project(CurvesProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

add_subdirectory(curves)

add_executable(task task/main.cpp "task/CurveLogger.h" "task/CLIParams.h")
target_link_libraries(task PRIVATE curves OpenMP::OpenMP_CXX)

if(WIN32)
    add_custom_command(TARGET task POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:curves>
            $<TARGET_FILE_DIR:task>
        COMMENT "Copying DLL to executable directory"
    )
endif()