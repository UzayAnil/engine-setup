cmake_minimum_required(VERSION 3.20)
project(app)

# need gl
find_package(OpenGL REQUIRED)

# files to build
add_executable(app # WIN32
#util
util/implementations.c
util/window.c
util/input.c
util/fileread.c
util/lerp.c

#main
main.c
)

# includes
target_include_directories(app PRIVATE 
${CMAKE_SOURCE_DIR}/include/
${CMAKE_SOURCE_DIR}/include/sokol/
)

# compile flags
target_compile_options(app PRIVATE
    $<$<CONFIG:Release>:
        $<$<CXX_COMPILER_ID:MSVC>:/O2 /fp:fast> 
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O3 -ffast-math>
    >
)

# always get opengl
target_link_libraries(app PRIVATE OpenGL::GL)

# platform specific linking
if(WIN32)
    target_link_libraries(app PRIVATE
        user32
        gdi32
        shell32
    )
else() # linux
    find_package(X11 REQUIRED)
    target_link_libraries(app PRIVATE 
        X11 
        Xi
        Xcursor
        m 
        pthread 
        dl
    )
endif()

# copy assets
add_custom_command(
    TARGET app 
    POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/res"
            "$<TARGET_FILE_DIR:app>/res"
)