#include "game.h"
using namespace std;

Game::Game(string name,shared_ptr<Player>host): name{name},host{host}{
    if(name.empty() || host == nullptr) throw runtime_error("Game Konstruktor");
}

string Game::get_name() const{
    return name;
}
bool Game::is_allowed(int n) const{ // evtl checken ob es das objekt überhaupt gibt
    int mmr_host = host->get_mmr();
    return (mmr_host*10<n*11 && mmr_host > n*9);
}

bool Game::remove_player(const GameKey& gk, shared_ptr<Player> p){
    if(players.find(p->get_name()) == player.end()) return false;
    else{
        players.erase
    }

}

