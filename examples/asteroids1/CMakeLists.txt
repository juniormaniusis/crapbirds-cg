project(asteroids1)

add_executable(${PROJECT_NAME} main.cpp openglwindow.cpp asteroids.cpp
                               ship.cpp nuvens.cpp pipe.cpp)

enable_abcg(${PROJECT_NAME})
