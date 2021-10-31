project(asteroids1)

add_executable(${PROJECT_NAME} main.cpp openglwindow.cpp asteroids.cpp
                               bird.cpp nuvens.cpp pipe.cpp)

enable_abcg(${PROJECT_NAME})
