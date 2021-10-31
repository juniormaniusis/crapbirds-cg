project(fastbirds)

add_executable(${PROJECT_NAME} main.cpp openglwindow.cpp
                               bird.cpp nuvens.cpp pipe.cpp)

enable_abcg(${PROJECT_NAME})
