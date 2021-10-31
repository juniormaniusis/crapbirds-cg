#include "pipe.hpp"

#include <cppitertools/itertools.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

void Pipes::initializeGL(GLuint program, const Ship &ship, int quantity) {
  terminateGL();

  m_program = program;
  m_colorLoc = abcg::glGetUniformLocation(m_program, "color");
  m_translationLoc = abcg::glGetUniformLocation(m_program, "translation");

  m_pipes.clear();
  m_pipes.resize(quantity);

  m_pipes[0] = createPipe(glm::vec2{0, .9});
  m_pipes[1] = createPipe(glm::vec2{0, -0.9f});
}

void Pipes::paintGL() {
  abcg::glUseProgram(m_program);

  for (const auto &pipe : m_pipes) {
    abcg::glBindVertexArray(pipe.m_vao);

    abcg::glUniform1f(m_scaleLoc, 1);
    abcg::glUniform1f(m_rotationLoc, 0);

    abcg::glUniform2f(m_translationLoc, pipe.m_translation.x,
                      pipe.m_translation.y);

    abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
    abcg::glBindVertexArray(0);
  }

  abcg::glUseProgram(0);
}

void Pipes::terminateGL() {
  for (auto pipe : m_pipes) {
    abcg::glDeleteBuffers(1, &pipe.m_vbo);
    abcg::glDeleteVertexArrays(1, &pipe.m_vao);
  }
}

Pipes::Pipe Pipes::createPipe(glm::vec2 translation) {
  Pipe pipe;

  pipe.m_color.a = 1.0f;

  pipe.width = 20;
  pipe.height = .5;

  std::vector<glm::vec2> positions({
      glm::vec2{-pipe.width / 2, pipe.height / 2},   // a
      glm::vec2{-pipe.width / 2, -pipe.height / 2},  // d
      glm::vec2{pipe.width / 2, -pipe.height / 2},   // c

      glm::vec2{-pipe.width / 2, pipe.height / 2},  // a
      glm::vec2{pipe.width / 2, pipe.height / 2},   // b
      glm::vec2{pipe.width / 2, -pipe.height / 2},  // c
  });

  pipe.m_translation = translation;

  abcg::glGenBuffers(1, &pipe.m_vbo);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, pipe.m_vbo);
  abcg::glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec2),
                     positions.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // obtem os atributos
  GLint positionAttribute{abcg::glGetAttribLocation(m_program, "inPosition")};

  // cria o VAO
  abcg::glGenVertexArrays(1, &pipe.m_vao);

  // assinala os VBOs para o VAO
  abcg::glBindVertexArray(pipe.m_vao);

  abcg::glBindBuffer(GL_ARRAY_BUFFER, pipe.m_vbo);
  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // encerra o assinalamento
  abcg::glBindVertexArray(0);

  return pipe;
}

void Pipes::update(const Ship &ship, float deltaTime) {
  for (auto &pipe : m_pipes) {
    pipe.m_translation.x = ship.m_translation.x;
    pipe.m_translation.y =
        pipe.m_translation.y - (ship.m_velocity.y * deltaTime);
  }
}