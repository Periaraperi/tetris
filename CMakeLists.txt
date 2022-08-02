cmake_minimum_required(VERSION 3.10)

project(tetris)
                                        
set(SRC main.cpp
    vector3.h
    texture_manager.h texture_manager.cpp 
    tetris.h tetris.cpp tetromino.h tetromino.cpp)

add_executable(${PROJECT_NAME} ${SRC})

if(WIN32)

target_include_directories(${PROJECT_NAME} PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/external/sdl2-64-mingw32/include/)
                
target_link_libraries(${PROJECT_NAME} PRIVATE
                      ${CMAKE_CURRENT_SOURCE_DIR}/external/sdl2-64-mingw32/lib/libSDL2.dll.a
                      ${CMAKE_CURRENT_SOURCE_DIR}/external/sdl2-64-mingw32/lib/libSDL2main.a
                      ${CMAKE_CURRENT_SOURCE_DIR}/external/sdl2-64-mingw32/lib/libSDL2_ttf.dll.a
                      )

endif()