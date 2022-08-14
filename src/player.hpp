#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player
{
private:
   std::string name;
   int highscore=0;
public:
  Player() {};
  Player(std::string _name): name{_name} {};
  Player(std::string _name, int _score): name{_name}, highscore{_score} {};
  std::string getName() {return name;};
  int getScore() const {return highscore;};
  void setScore(int score) {highscore=score;};
};

#endif