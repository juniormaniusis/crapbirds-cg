#ifndef STARLAYERS_HPP_
#define STARLAYERS_HPP_

#include <array>
#include <random>

#include "abcg.hpp"
#include "gamedata.hpp"
#include "ship.hpp"

class OpenGLWindow;

class StarLayers {
 public:
  void initializeGL(GLuint program, int quantity);
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

  struct Nuvem {
    GLuint m_vao{};
    GLuint m_vbo{};
    glm::vec4 m_color {.5, .5, .5, .5};
    glm::vec2 m_translation{glm::vec2(0)};
  };

  std::array<Nuvem, 1> m_nuvens;

  std::default_random_engine m_randomEngine;

  StarLayers::Nuvem createNuvem();
};

#endif