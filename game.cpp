#include "game.h"
using namespace std;

Game::Game(string name,shared_ptr<Player>host): name{name},host{host}{
    if(name.empty() || host == nullptr) throw runtime_error("Game Konstruktor"); // schauen ob host geht
}

string Game::get_name() const{
    return name;
}
bool Game::is_allowed(int n) const{
    int mmr_host = host.lock()->get_mmr(); //int mmr_host = host->get_mmr();
    return (mmr_host*10<n*11 && mmr_host > n*9);
}

bool Game::remove_player(const GameKey& gk, shared_ptr<Player> p){
    if(players.find(p->get_name()) == player.end()) return false;
    else{
        players.erase(players.find(p->get_nacme()));
        return true;
    }

}

bool Game::add_player(const GameKey& gk, shared_ptr<Player> p){
bool stop = (is_allowed(p.get()->get_mmr()) || players.find(p.get()->get_name())!=players.end()); // sollte so stimmen
if(stop)
    return false;
else {
    players.insert({p.get()->get_name(),p});
    return true;

}

}


// Kopie

using pairtype = pair<string,weak_ptr<Player>>;
weak_ptr<Player> Game::best_player() const {
    if(players.size()==0) {throw runtime_error("");}

    auto it = max_element(players.begin(), players.end(), [] (const pairtype& p1, const pairtype& p2) {
        return p1.second.lock().get()->get_mmr()<p2.second.lock().get()->get_mmr();
    });

    return it->second;
}

size_t Game::number_of_players() const {
    return players.size();
}


weak_ptr<Player> Game::play(size_t i) {
    if(i>=players.size()||host.expired()) {throw runtime_error("");}


    int pos=0;
    for_each(players.begin(), players.end(), [this,i,pos] (const pairtype& p) {
        if(pos!=i) {
            if(p.second.lock().get()->get_mmr()>best_player().lock().get()->get_mmr()) {
                p.second.lock().get()->change_mmr(change(false));
            }
            p.second.lock().get()->change_mmr(change(false));
        }
    });


    auto it = players.begin();
    for(size_t k=0;k<i;k++) {
        k++;
    }

    it->second.lock().get()->change_mmr(change(true));

    return it->second;
}



ostream& Game::print(ostream& o) const {

    o << "[" << get_name() << ", " << host.lock().get()->get_name() << host.lock().get()->get_mmr() << ", player: {";
    auto it = players.begin();
    for(size_t i=0;i<players.size();i++) {
        if((i+1)<players.size()) {
            o << it->second.lock().get()->get_name() << ", " << it->second.lock().get()->get_mmr();
            it++;
        }
        else{
            o << it->second.lock().get()->get_name();
        }
    }
    o << "}]";
    return o;

}

ostream& operator<<(ostream& os, const Game& g) {
    return g.print(os);
}

ostream& operator<<(ostream& os, const UGame& g) {
    return g.print(os);
}

ostream& operator<<(ostream& os, const RGame& g) {
    return g.print(os);
}

// RGame

RGame::RGame(string s, shared_ptr<Player> p):Game(s,p) {

}

int RGame::change(bool won) const {
    if(won) {return 5;}
    return -5;
}


ostream& RGame::print(ostream& o) const {
    o << "Ranked Game: ";
    return Game::print(o);
}


// UGame

UGame::UGame(string s,shared_ptr<Player> p):Game(s,p) {

}

int UGame::change(bool) const {
    return 0;
}

ostream& UGame::print(ostream& o) const {
    o << "Unranked Game: ";
    return Game::print(o);
}



