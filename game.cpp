#include "game.h"
#include "player.h"
using namespace std;


Game::Game(string name,shared_ptr<Player> host): name{name}, host{host} {
if(name.empty() || host == nullptr) throw runtime_error("game constructor");

}