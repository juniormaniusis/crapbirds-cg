
#ifndef PIPE_HPP_
#define PIPE_HPP_

#include <list>
#include <random>

#include "abcg.hpp"
#include "gamedata.hpp"
#include "ship.hpp"

class OpenGLWindow;

class Pipes {
 public:
  void initializeGL(GLuint program, const Ship &ship, int quantity);
  // void initializeGL(GLuint program, int quantity);
  void paintGL();
  void terminateGL();

  void update(const Ship &ship, float deltaTime);

 private:
  friend OpenGLWindow;

  GLuint m_program{};
  GLint m_colorLoc{};
  GLint m_rotationLoc{};
  GLint m_translationLoc{};
  GLint m_scaleLoc{};

  struct Pipe {
    GLuint m_vao{};
    GLuint m_vbo{};

    glm::vec4 m_color{0, 1, 0, 1};
    bool m_hit{false};
    float height{};
    float width{};
    
    glm::vec2 m_translation{glm::vec2(0)};
    
    glm::vec2 m_velocity{glm::vec2(-2, 0)};
  };

  std::vector<Pipe> m_pipes;

  std::default_random_engine m_randomEngine;
  std::uniform_real_distribution<float> m_randomDist{-1.0f, 1.0f};

  Pipes::Pipe createPipe(glm::vec2 translation = glm::vec2(0));
};

#endif