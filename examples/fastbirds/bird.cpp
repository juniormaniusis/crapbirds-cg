#include "bird.hpp"

#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/rotate_vector.hpp>

void Bird::initializeGL(GLuint program) {
  terminateGL();

  m_program = program;
  m_colorLoc = abcg::glGetUniformLocation(m_program, "color");
  m_rotationLoc = abcg::glGetUniformLocation(m_program, "rotation");
  m_scaleLoc = abcg::glGetUniformLocation(m_program, "scale");
  m_translationLoc = abcg::glGetUniformLocation(m_program, "translation");

  m_rotation = 0.0f;
  m_translation = glm::vec2(0);
  m_velocity = glm::vec2(2, 0);

  int A, B, C, D, E, F, G, H, I, J, K, L, M, N, O;
  A = 0;
  B = 1;
  C = 2;
  D = 3;
  E = 4;
  F = 5;
  G = 6;
  H = 7;
  I = 8;
  J = 9;
  K = 10;
  L = 11;
  M = 12;
  N = 13;
  O = 14;

  std::array<glm::vec2, 15> positions{
      glm::vec2{-10, 4},       glm::vec2{5.48, -4},    glm::vec2{-2.7, -1.3},
      glm::vec2{-1.02, -1.39}, glm::vec2{0.58, 0.29},  glm::vec2{-1.08, 0.35},
      glm::vec2{-1, 2},        glm::vec2{-4.32, 5.18}, glm::vec2{-1.06, 5.18},
      glm::vec2{2.13, 1.94},   glm::vec2{0.62, 1.97},  glm::vec2{2.21, 5.28},
      glm::vec2{0.54, 3.66},   glm::vec2{3.77, 3.71},  glm::vec2{2.17, 3.70},
  };

  // Normalize
  for (auto &position : positions) {
    position /= glm::vec2{5.48, 5.18f};
    position *= 1.20;
  }

  const std::array indices{C, D, E, E, F, C, F, K, E, F, G, K, K, J,
                           E, G, I, J, G, H, I, J, M, L, L, O, N};

  auto branco = glm::vec4{.84, .11, .25, 1};
  auto cinza = glm::vec4{.97, .89, .33, 1};
  auto laranja = glm::vec4{.88, .45, .27, 1};

  std::array<glm::vec4, 27> colors{
      cinza, cinza, cinza, branco, branco, branco, branco, branco, branco,
      cinza, cinza, cinza, branco, branco, branco, branco, branco, branco,
      cinza, cinza, cinza, branco, branco, laranja, laranja, laranja, laranja};

  // cria o VBO de posições
  abcg::glGenBuffers(1, &m_vbo);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // cria o vbo de posicoes
  abcg::glGenBuffers(1, &m_color_vbo);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_color_vbo);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // cria o EBO (indices)
  abcg::glGenBuffers(1, &m_ebo);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  abcg::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // atributos
  GLint positionAttribute{abcg::glGetAttribLocation(m_program, "inPosition")};
  GLint colorAttribute{abcg::glGetAttribLocation(m_program, "inColor")};

  // cria o VAO
  abcg::glGenVertexArrays(1, &m_vao);

  // assinala os VBOS no VAO
  abcg::glBindVertexArray(m_vao);

  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);


  abcg::glEnableVertexAttribArray(colorAttribute);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_color_vbo);
  abcg::glVertexAttribPointer(colorAttribute, 4, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);


  // encerra a atribuicao
  abcg::glBindVertexArray(0);
}

void Bird::paintGL(const GameData &gameData) {
  if (gameData.m_state != State::Playing) return;

  abcg::glUseProgram(m_program);

  abcg::glBindVertexArray(m_vao);

  abcg::glUniform1f(m_scaleLoc, m_scale);
  abcg::glUniform1f(m_rotationLoc, m_rotation);
  abcg::glUniform2fv(m_translationLoc, 1, &m_translation.x);

  abcg::glUniform4f(m_colorLoc, 0, 1, 0, 0);
  abcg::glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, nullptr);

  abcg::glBindVertexArray(0);

  abcg::glUseProgram(0);
}

void Bird::terminateGL() {
  abcg::glDeleteBuffers(1, &m_vbo);
  abcg::glDeleteBuffers(1, &m_ebo);
  abcg::glDeleteBuffers(1, &m_color_vbo);

  abcg::glDeleteVertexArrays(1, &m_vao);
}
float min(float a, float b) { return a <= b ? a : b; }
float max(float a, float b) { return a >= b ? a : b; }
void Bird::update(const GameData &gameData, float deltaTime) {
  
  // se a velocidade do passaro, no eixo y for positiva, a rotação é aplicada no sentido anti horario
  // caso contrario, no sentido horario
  if (m_velocity.y >= 0) {
    m_rotation =
        glm::wrapAngle(m_rotation + glm::length(m_velocity) * deltaTime);

  } else {
    m_rotation =
        glm::wrapAngle(m_rotation - glm::length(m_velocity) * deltaTime);
  }
  
  // manter o angulo entre 0 e 2pi
  m_rotation = glm::wrapAngle(m_rotation);

  // aplica a gravidade
  m_velocity += glm::vec2(0, -4.2) * deltaTime;

  // se o jogador clicar, aplica uma força para cima, interrompendo sua queda.
  if (gameData.m_input[static_cast<size_t>(Input::Fire)] &&
      gameData.m_state == State::Playing) {
    m_velocity.y = 3;
  }
}