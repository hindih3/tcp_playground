add_library(netlib STATIC
    src/netlib.c
)

target_include_directories(netlib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)