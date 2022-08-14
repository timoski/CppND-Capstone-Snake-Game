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
   MenuOption showMenu() const;
   void showHighscore() const;
   Player addPlayer() const;
   Player selectPlayer() const;
   void saveScore(Player player) const;
private:
   std::vector<Player> getPlayers() const;
};

