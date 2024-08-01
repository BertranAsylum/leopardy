file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(leopardy WIN32 ${SOURCES})

target_link_libraries(leopardy PRIVATE d2d1.lib dwrite.lib Ws2_32.lib)
target_include_directories(leopardy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(leopardy
    PRIVATE UNICODE
    PRIVATE WIN32_LEAN_AND_MEAN
)
