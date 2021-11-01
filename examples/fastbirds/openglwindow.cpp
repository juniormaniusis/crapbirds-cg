#include "openglwindow.hpp"

#include <imgui.h>

#include "abcg.hpp"

void OpenGLWindow::checkCollisions() {
  auto upper_pipe = m_pipes.m_pipes[0];
  auto bottom_pipe = m_pipes.m_pipes[1];

  if (upper_pipe.m_translation.y < 0.003 ||
      bottom_pipe.m_translation.y > 0.003) {
    m_gameData.m_state = State::GameOver;
    m_restartWaitTimer.restart();
  }
}

void OpenGLWindow::handleEvent(SDL_Event &event) {
  // Keyboard events
  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
    m_gameData.m_input.set(static_cast<size_t>(Input::Jump));
  }

  if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE) {
    m_gameData.m_input.reset(static_cast<size_t>(Input::Jump));
  }

  if (event.type == SDL_MOUSEBUTTONDOWN &&
      event.button.button == SDL_BUTTON_LEFT) {
    m_gameData.m_input.set(static_cast<size_t>(Input::Jump));
  }
  
  if (event.type == SDL_MOUSEBUTTONUP &&
      event.button.button == SDL_BUTTON_LEFT) {
    m_gameData.m_input.reset(static_cast<size_t>(Input::Jump));
  }
}

void OpenGLWindow::initializeGL() {
  // Load a new font
  ImGuiIO &io{ImGui::GetIO()};
  auto filename{getAssetsPath() + "AngryBirdsMovie.ttf"};
  m_font = io.Fonts->AddFontFromFileTTF(filename.c_str(), 45.0f);
  m_font_score = io.Fonts->AddFontFromFileTTF(filename.c_str(), 20.0f);
  if (m_font == nullptr || m_font_score == nullptr) {
    throw abcg::Exception{abcg::Exception::Runtime("Cannot load font file")};
  }

  // Create program to render the other objects
  m_objectsProgram = createProgramFromFile(getAssetsPath() + "objects.vert",
                                           getAssetsPath() + "objects.frag");

  abcg::glClearColor(.53, .61, .92, 0);

#if !defined(__EMSCRIPTEN__)
  abcg::glEnable(GL_PROGRAM_POINT_SIZE);
#endif

  // Start pseudo-random number generator
  m_randomEngine.seed(
      std::chrono::steady_clock::now().time_since_epoch().count());

  restart();
}

void OpenGLWindow::restart() {
  m_gameData.m_state = State::Playing;
  m_nuvens.initializeGL(m_objectsProgram);
  m_bird.initializeGL(m_objectsProgram);
  m_pipes.initializeGL(m_objectsProgram, m_bird, 2);
}

void OpenGLWindow::update() {
  float deltaTime{static_cast<float>(getDeltaTime())};
  if (m_gameData.m_state == State::Playing) {
    m_gameData.score += glm::ceil(deltaTime);
  }
  // Wait 5 seconds before restarting
  if (m_gameData.m_state != State::Playing &&
      m_restartWaitTimer.elapsed() > 5) {
    restart();
    return;
  }

  m_bird.update(m_gameData, deltaTime);
  m_nuvens.update(m_bird, deltaTime);
  m_pipes.update(m_bird, deltaTime);

  if (m_gameData.m_state == State::Playing) {
    checkCollisions();
  }
}

void OpenGLWindow::paintGL() {
  update();

  abcg::glClear(GL_COLOR_BUFFER_BIT);
  abcg::glViewport(0, 0, m_viewportWidth, m_viewportHeight);

  m_nuvens.paintGL();
  m_bird.paintGL(m_gameData);
  m_pipes.paintGL();
}

void OpenGLWindow::paintUI() {
  abcg::OpenGLWindow::paintUI();

  {
    const auto size{ImVec2(300, 85)};
    const auto position{ImVec2((m_viewportWidth - size.x) / 2.0f,
                               (m_viewportHeight - size.y) / 2.0f)};
    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size);
    ImGuiWindowFlags flags{ImGuiWindowFlags_NoBackground |
                           ImGuiWindowFlags_NoTitleBar |
                           ImGuiWindowFlags_NoInputs};
    ImGui::Begin(" ", nullptr, flags);
    ImGui::PushFont(m_font);
    if (m_gameData.m_state == State::GameOver) {
      ImGui::Text("Game Over!");

      ImGui::PushFont(m_font_score);
      ImGui::Text("Your Score: %ld", m_gameData.score);
      ImGui::PopFont();
    }

    ImGui::PopFont();
    ImGui::End();
  }
}

void OpenGLWindow::resizeGL(int width, int height) {
  m_viewportWidth = width;
  m_viewportHeight = height;

  abcg::glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLWindow::terminateGL() {
  abcg::glDeleteProgram(m_objectsProgram);
  m_bird.terminateGL();
  m_nuvens.terminateGL();
  m_pipes.terminateGL();
}