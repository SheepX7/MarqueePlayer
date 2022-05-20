project(simple_gme)

add_library(gme
        SHARED
        op.cpp)

target_link_libraries(
        gme
)