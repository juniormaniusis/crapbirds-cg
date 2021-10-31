#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

#include <bitset>

enum class Input { Right, Left, Down, Up, Jump };
enum class State { Playing, GameOver };

struct GameData {
  State m_state{State::Playing};
  std::bitset<5> m_input; 
  long score = 0; // pontuação do jogador
};

#endif