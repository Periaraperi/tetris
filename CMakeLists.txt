cmake_minimum_required(VERSION 3.10)

project(tetris)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)                                   
set(SRC main.cpp
    vector3.h
    texture_manager.h texture_manager.cpp 
    tetris.h tetris.cpp tetromino.h tetromino.cpp)

add_executable(${PROJECT_NAME} ${SRC})

<<<<<<< HEAD
if (WIN32)
=======
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

if(UNIX)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
    
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
                
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})


endif()

if(WIN32)
>>>>>>> 7279f7479b37c879992238731e1f1a5c9b9cf82f

target_include_directories(${PROJECT_NAME} PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/external/sdl2-64-mingw32/include/)
                
target_link_libraries(${PROJECT_NAME} PRIVATE
                      ${CMAKE_CURRENT_SOURCE_DIR}/external/sdl2-64-mingw32/lib/libSDL2.dll.a
                      ${CMAKE_CURRENT_SOURCE_DIR}/external/sdl2-64-mingw32/lib/libSDL2main.a
                      ${CMAKE_CURRENT_SOURCE_DIR}/external/sdl2-64-mingw32/lib/libSDL2_ttf.dll.a
                      )

<<<<<<< HEAD
endif ()

if (UNIX)

find_package(SDL2 REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} /usr/include/SDL2)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} /usr/lib/libSDL2_ttf.so)

endif ()
=======
endif()
>>>>>>> 7279f7479b37c879992238731e1f1a5c9b9cf82f
