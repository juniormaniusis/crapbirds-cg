#include "pipe.hpp"

#include <cppitertools/itertools.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

void Pipes::initializeGL(GLuint program, int quantity) {
  terminateGL();

  //   // Start pseudo-random number generator
  //   m_randomEngine.seed(
  //       std::chrono::steady_clock::now().time_since_epoch().count());

  m_program = program;
  m_colorLoc = abcg::glGetUniformLocation(m_program, "color");
  // m_rotationLoc = abcg::glGetUniformLocation(m_program, "rotation");
  m_scaleLoc = abcg::glGetUniformLocation(m_program, "scale");
  m_translationLoc = abcg::glGetUniformLocation(m_program, "translation");

  //   // Create asteroids
  m_pipes.clear();
  m_pipes.resize(quantity);

  for (auto &pipe : m_pipes) {
    pipe = createPipe();

    // Make sure the pipe won't collide with the ship
    //   do {
    pipe.m_translation = {m_randomDist(m_randomEngine),
                          m_randomDist(m_randomEngine)};
    //   } while (glm::length(pipe.m_translation) < 0.5f);
  }
}

void Pipes::paintGL() {
  abcg::glUseProgram(m_program);

  for (const auto &asteroid : m_pipes) {
    abcg::glBindVertexArray(asteroid.m_vao);

    abcg::glUniform4fv(m_colorLoc, 1, &asteroid.m_color.r);
    // abcg::glUniform1f(m_scaleLoc, asteroid.m_scale);
    // abcg::glUniform1f(m_rotationLoc, asteroid.m_rotation);

    for (auto i : {-2, 0, 2}) {
      for (auto j : {-2, 0, 2}) {
        abcg::glUniform2f(m_translationLoc, asteroid.m_translation.x + j,
                          asteroid.m_translation.y + i);

        // abcg::glDrawArrays(GL_TRIANGLE_FAN, 0, asteroid.m_polygonSides + 2);
        abcg::glDrawArrays(GL_LINE_LOOP, 0, 5);
      }
    }

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

  //   auto &re{m_randomEngine};  // Shortcut

  // Randomly choose the number of sides
  //   std::uniform_int_distribution<int> randomSides(6, 20);
  //   pipe.m_polygonSides = randomSides(re);

  // Choose a random color (actually, a grayscale)
  //   std::uniform_real_distribution<float> randomIntensity(0.5f, 1.0f);
  //   pipe.m_color = glm::vec4(1) * randomIntensity(re);

  //   pipe.m_color.a = 1.0f;
  //   pipe.m_scale = scale;

  // Choose a random direction
  //   glm::vec2 direction{m_randomDist(re), m_randomDist(re)};

  // Create geometry
  std::vector<glm::vec2> positions({
      glm::vec2{0, 0},
      glm::vec2{0, 2},
      glm::vec2{1, 2},
      glm::vec2{1, 0},
      glm::vec2{0, 0},
  });

  //   const auto step{M_PI * 2 / asteroid.m_polygonSides};
  //   std::uniform_real_distribution<float> randomRadius(0.8f, 1.0f);
  //   for (const auto angle : iter::range(0.0, M_PI * 2, step)) {
  //     const auto radius{randomRadius(re)};
  //     positions.emplace_back(radius * std::cos(angle), radius *
  //     std::sin(angle));
  //   }
  //   positions.push_back(positions.at(1));

  // Generate VBO
  abcg::glGenBuffers(1, &pipe.m_vbo);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, pipe.m_vbo);
  abcg::glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec2),
                     positions.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Get location of attributes in the program
  GLint positionAttribute{abcg::glGetAttribLocation(m_program, "inPosition")};

  // Create VAO
  abcg::glGenVertexArrays(1, &pipe.m_vao);

  // Bind vertex attributes to current VAO
  abcg::glBindVertexArray(pipe.m_vao);

  abcg::glBindBuffer(GL_ARRAY_BUFFER, pipe.m_vbo);
  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // End of binding to current VAO
  abcg::glBindVertexArray(0);

  return pipe;
}

void Pipes::update(const Ship &ship, float deltaTime) {
  for (auto &pipe : m_pipes) {
    printf("pipe\nx=%f; y=%f", pipe.m_translation.x, pipe.m_translation.y);
    // pipe.m_translation -= ship.m_velocity * deltaTime;
    // pipe.m_translation += pipe.m_velocity * deltaTime;

    // // Wrap-around
    // if (pipe.m_translation.x < -1.0f) pipe.m_translation.x += 2.0f;
    // if (pipe.m_translation.x > +1.0f) pipe.m_translation.x -= 2.0f;
    // if (pipe.m_translation.y < -1.0f) pipe.m_translation.y += 2.0f;
    // if (pipe.m_translation.y > +1.0f) pipe.m_translation.y -= 2.0f;
  }
}