#ifndef nuvens_HPP_
#define nuvens_HPP_

#include <array>
#include <random>

#include "abcg.hpp"
#include "gamedata.hpp"
#include "ship.hpp"

class OpenGLWindow;

class nuvens {
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
    GLuint m_color_vbo{};
    glm::vec2 m_translation{glm::vec2(0)};
    int tipo;
    int qtd_pts;
  };

  std::array<Nuvem, 4> m_nuvens;

  std::default_random_engine m_randomEngine;

  nuvens::Nuvem createNuvem(int model);
};

#endif