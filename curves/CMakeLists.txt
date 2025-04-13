add_library(curves SHARED 
    src/curves.cpp
    include/curves/curves.h
)

target_compile_definitions(curves PRIVATE 
    $<$<BOOL:${WIN32}>:CURVES_BUILD_DLL>
)

target_include_directories(curves PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)