#include "nuvens.hpp"

#include <cppitertools/itertools.hpp>

void nuvens::initializeGL(GLuint program) {
  terminateGL();
  m_randomEngine.seed(
      std::chrono::steady_clock::now().time_since_epoch().count());

  m_program = program;
  m_colorLoc = abcg::glGetUniformLocation(m_program, "color");
  m_translationLoc = abcg::glGetUniformLocation(m_program, "translation");

  std::uniform_real_distribution<float> faixa(0, 1.0f);

  // para cada nuvens, definir a sua aparencia
  for (auto &&[index, nuvem] : iter::enumerate(m_nuvens)) {
    auto sorteado{faixa(m_randomEngine)};

    if (sorteado > .3) {
      nuvem = createNuvem(1);
    } else {
      nuvem = createNuvem(2);
    }
  }
}

std::vector<glm::vec4> getModel1Colors() {
  auto azul = glm::vec4{.84, .92, 1, .7};
  auto azulc = glm::vec4{.76, .82, .87, .7};

  std::vector<glm::vec4> colors{azulc, azulc, azulc, azulc, azulc,
                                azulc, azulc, azul,  azulc, azul,
                                azulc, azulc, azulc, azulc, azul};
  return colors;
}

std::vector<glm::vec4> getModel2Colors() {
  auto azul = glm::vec4{.84, .92, 1, .7};
  auto azulc = glm::vec4{.76, .82, .87, .7};

  std::vector<glm::vec4> colors{azulc, azulc, azulc, azulc, azulc, azulc,
                                azulc, azul,  azulc, azul,  azulc, azulc,
                                azulc, azulc, azul,  azulc, azulc, azulc};

  return colors;
}

std::vector<glm::vec2> getModel2Positions() {
  std::vector<glm::vec2> positions{
      glm::vec2{0, 1}, glm::vec2{0, 0}, glm::vec2{4, 0},

      glm::vec2{0, 1}, glm::vec2{4, 0}, glm::vec2{4, 1},

      glm::vec2{4, 1}, glm::vec2{3, 2}, glm::vec2{4, 2},

      glm::vec2{4, 1}, glm::vec2{3, 2}, glm::vec2{3, 1},

      glm::vec2{1, 2}, glm::vec2{2, 2}, glm::vec2{2, 1},

      glm::vec2{1, 2}, glm::vec2{2, 1}, glm::vec2{1, 1},

  };
  for (int i = 0; i < (int)positions.size(); i++) {
    positions[i] /= glm::vec2{4, 2};
  }
  return positions;
}

std::vector<glm::vec2> getModel1Positions() {
  // pontos das nuvens
  glm::vec2 A, B, C, D, E, F, G, H, I;

  A = glm::vec2{-6.34, -3.9};
  B = glm::vec2{5.65, -3.9};
  C = glm::vec2{-4.62, 2.64};
  D = glm::vec2{4.38, 2.58};
  E = glm::vec2{-0.34, 6.56};
  F = glm::vec2{-3.6, 5.6};
  G = glm::vec2{3.36, 5.42};
  H = glm::vec2{-5.16, 3.98};
  I = glm::vec2{4.62, 3.7};

  std::vector<glm::vec2> positions{C, H, F, C, F, E, C, E, D, E, D, G, D, G, I};

  for (int i = 0; i < (int)positions.size(); i++) {
    positions[i] /= glm::vec2{6.34, 6.56};
    positions[i] *= 1.3;
  }

  return positions;
}

nuvens::Nuvem nuvens::createNuvem(int tipo_nuvem = 2) {
  Nuvem nuvem;

  m_randomEngine.seed(
      std::chrono::steady_clock::now().time_since_epoch().count());

  std::uniform_real_distribution<float> faixaPontos(-1, 1);
  std::uniform_real_distribution<float> velocidade(1, 1.5);
  nuvem.m_translation.y = faixaPontos(m_randomEngine);
  nuvem.m_translation.x = faixaPontos(m_randomEngine);
  nuvem.fator_velocidade = velocidade(m_randomEngine);

  // define o formato da nuvem
  std::vector<glm::vec2> positions;
  std::vector<glm::vec4> colors;
  nuvem.tipo = tipo_nuvem;

  if (tipo_nuvem == 1) {
    positions = getModel1Positions();
    colors = getModel1Colors();
  } else {
    positions = getModel2Positions();
    colors = getModel2Colors();
  }
  nuvem.qtd_pts = positions.size();

  // cria o VBO de posição
  abcg::glGenBuffers(1, &nuvem.m_vbo);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, nuvem.m_vbo);
  abcg::glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec2),
                     positions.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // cria o VBO de cores

  abcg::glGenBuffers(1, &nuvem.m_color_vbo);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, nuvem.m_color_vbo);
  abcg::glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec4),
                     colors.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // pega os atributos
  const auto positionAttribute{
      abcg::glGetAttribLocation(m_program, "inPosition")};
  const auto colorAttribute{abcg::glGetAttribLocation(m_program, "inColor")};

  // cria o VAO
  abcg::glGenVertexArrays(1, &nuvem.m_vao);

  // vincula os VBOS ao VAO
  abcg::glBindVertexArray(nuvem.m_vao);

  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, nuvem.m_vbo);
  abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  abcg::glEnableVertexAttribArray(colorAttribute);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, nuvem.m_color_vbo);
  abcg::glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // End of binding to current VAO
  abcg::glBindVertexArray(0);
  return nuvem;
}

void nuvens::paintGL() {
  abcg::glUseProgram(m_program);

  for (const auto &nuvem : m_nuvens) {
    abcg::glBindVertexArray(nuvem.m_vao);

    for (auto i : {-2, 0, 2}) {
      for (auto j : {-2, 0, 2}) {
        abcg::glUniform2f(m_translationLoc, nuvem.m_translation.x + j,
                          nuvem.m_translation.y + i);
        abcg::glEnable(GL_BLEND);
        abcg::glDrawArrays(GL_TRIANGLES, 0, nuvem.qtd_pts);
      }
    }
    abcg::glBindVertexArray(0);
  }
  abcg::glUseProgram(0);
}

void nuvens::terminateGL() {
  for (auto &nuvem : m_nuvens) {
    abcg::glDeleteBuffers(1, &nuvem.m_vbo);
    abcg::glDeleteBuffers(1, &nuvem.m_color_vbo);
    abcg::glDeleteVertexArrays(1, &nuvem.m_vao);
  }
}

void nuvens::update(const Ship &ship, float deltaTime) {
  for (auto &&[index, nuvem] : iter::enumerate(m_nuvens)) {
    const auto layerSpeedScale{1.0f / (index + 2.0f)};
    nuvem.m_translation -= ship.m_velocity * deltaTime * layerSpeedScale;

    if (nuvem.m_translation.x < -1.0f) nuvem.m_translation.x += 2.0f;
    if (nuvem.m_translation.x > +1.0f) nuvem.m_translation.x -= 2.0f;
    if (nuvem.m_translation.y < -1.0f) nuvem.m_translation.y += 2.0f;
    if (nuvem.m_translation.y > +1.0f) nuvem.m_translation.y -= 2.0f;
  }
}