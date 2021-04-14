#include <iostream>
#include <memory>
#include <string>
#include "game.cpp"


class Game{
  string name;
  weak_ptr<Player> host;
  map<string,weak_ptr<Player>> players;

}
