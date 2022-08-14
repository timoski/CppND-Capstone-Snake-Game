#include <iostream>
#include <exception>
#include "gamemenuinterface.hpp"
#include <fstream>

MenuOption GameMenuInterface::showMenu()
{
  while(true)
  {
    std::cout << "Select from Options:" << std::endl;
    std::cout << "Show Highscore : 0" << std::endl;
    std::cout << "New Player: 1" << std::endl;
    std::cout << "Select Player: 2" << std::endl;
  
    std::string selectedStr;
    MenuOption selectedOption;
    std::cin >> selectedStr;
    try
    {
      selectedOption=static_cast<MenuOption>(stoi(selectedStr));
      return selectedOption;
    }
    catch(...)
    {
      std::cout << "Invalid selecton" << std::endl;
    }
  }
}

void  GameMenuInterface::saveScore(Player player)
{
  if(player.getScore() == 0)
  {
    return;
  }
  auto players = getPlayers();
  std::vector<Player> players2;
  bool playerInserted=false;
  for(auto& pl : players)
  {
    if(pl.getName().compare(player.getName())==0)
    {
      if(player.getScore() > pl.getScore())
      {
        //std::cout << "gmi:45 Pushback " << player.getName() << std::endl;
        players2.push_back(player);
        playerInserted=true;
        //std::cout << "gmi:45 " << player.getName() << std::endl;
        continue;
      }
      else
      {
        //std::cout << "gmi:50 Player:" << player.getName() << " pl: " << pl.getName() << std::endl;
        return;
      }
    }
         
    if(player.getScore()>pl.getScore())
    {
      //std::cout << "gmi:60 Pushback " << player.getName() << std::endl;
      players2.push_back(player);
      playerInserted=true;
    }
    //std::cout << "gmi:64 Pushback " << pl.getName() << std::endl;
    players2.push_back(pl);
  }
  if(!playerInserted)
  {
    //std::cout << "gmi:45 Pushback " << player.getName() << std::endl;
    players2.push_back(player);
    playerInserted=true;
  }
  //std::cout << "gmi:61 Size of players2: " << players2.size() << std::endl;
  std::ofstream highScoreStream("highscore.txt");
  for(auto& pl : players2)
  {
    highScoreStream<< pl.getName() << ":" << pl.getScore() << std::endl;
  } 
}

std::vector<Player> GameMenuInterface::getPlayers()
{
  std::vector<Player> players;
  std::ifstream highScoreStream("highscore.txt");
  if(highScoreStream.is_open())
  {
    std::string line;
    for( std::string line; getline( highScoreStream, line ); )
    {
      int pos=line.find(":");
      //std::cout << "Pos: " << pos << std::endl;
      std::string name=line.substr(0,pos);
      //std::cout << "Name: " << name << std::endl;
      //std::cout << "Number: " << line.substr(pos+1) << std::endl;
      int score=stoi(line.substr(pos+1));
      players.push_back(Player{name, score});
    }
  }
  else
  {
    std::ofstream newStream("highscore.txt");
  }
  return players; 
}

void GameMenuInterface::showHighscore()
{
  auto players=getPlayers();
  std::cout << "Highscores:" << std::endl;
  int i=0;
  for(auto& pl : players)
  {
    std::cout << ++i << ". " << pl.getName() << " : "  << pl.getScore() << std::endl;
  }
}

  
Player GameMenuInterface::addPlayer()
{
  std::cout << "Please enter your name: ";
  std::string name;
  std::cin >> name;
  return Player{name}; 
}

Player GameMenuInterface::selectPlayer()
{
  std::vector<Player> players = getPlayers();
  if(players.empty())
  {
    std::cout << "Empty List of Players. Create new one" << std::endl;
    return addPlayer();
  }
  while (true)
  {
    std::cout << "Please select From Following Players: " << std::endl;
    {
      int i=0; 
      for(Player& pl : players)
      {
        std::cout << i++ << ": " << pl.getName() << std::endl; 
      }
    }
    std::string selectedStr;
    std::cin >> selectedStr;
    int selection=0;
    try
    {
      selection=stoi(selectedStr);   
    }
    catch(...)
    {
      std::cout << "Invalid selection" << std::endl;
    }
    
    if((selection<0) || ((selection+1) > players.size()))
    {
      std::cout << "Invalid selection!" << std::endl;
    }
    else
    {
      return players[selection];
    }
  }
}


