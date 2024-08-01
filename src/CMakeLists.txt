file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(jeopardy WIN32 ${SOURCES})

target_link_libraries(jeopardy PRIVATE d2d1.lib dwrite.lib Ws2_32.lib)
target_include_directories(jeopardy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(jeopardy
    PRIVATE UNICODE
    PRIVATE WIN32_LEAN_AND_MEAN
)
