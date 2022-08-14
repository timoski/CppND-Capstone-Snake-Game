#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "gamemenuinterface.hpp"
//#include "highscore.hpp"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  Player player;
  //std::cout << "main:16" << std::endl;
  //std::cout << player.getName() << "17" << std::endl;
  GameMenuInterface gmi{};
  while(player.getName().empty())
  {
    //std::cout << "main:19" << std::endl;
    MenuOption mo=gmi.showMenu();
    switch(mo)
    {
      case MenuOption::showHighscore:
      {
        gmi.showHighscore();
        break;
      }
      case MenuOption::addPlayer:
      {
        player=gmi.addPlayer();
        break;
      }
      case MenuOption::selectPlayer:
      {
        player=gmi.selectPlayer();
        break;
      }  
    }
  }
  //Player player{""};
  //bool playerAdded{false};
  //while(!playerAdded)
  //{
  //  Highscore highscore{};
  //  std::string activePlayer=highscore.getActivePlayerString();
  //  std::cout << "Active Player: " << activePlayer << std::endl;
  //}
  //std::cout << "Please enter your name: ";
  //std::string name;
  //std::cin >> name;
  
  //player=Player{name};
  //{
  //  Highscore highscore{};
  //  playerAdded=highscore.addActivePlayer(player);
  //}
  //}
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  if(game.GetScore() > 0)
  {
    if(game.GetScore() > player.getScore())
    {
      player.setScore(game.GetScore());
      std::cout << "Congratulation this is your highscore!" << std::endl;
    }
    gmi.saveScore(player);
  }
  return 0;
}