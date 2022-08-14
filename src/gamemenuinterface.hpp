#include "player.hpp"
#include <vector>

enum class MenuOption
{
      showHighscore,
      addPlayer,
      selectPlayer
};
class GameMenuInterface
{
public: 
   MenuOption showMenu();
   void showHighscore();
   Player addPlayer();
   Player selectPlayer();
   std::vector<Player> getPlayers();
   void saveScore(Player player);
};

