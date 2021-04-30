

#include "game.h"
#include <algorithm>
// für jedes element der map = mypair
using mypair = pair<string,weak_ptr<Player>>;

// Konstruktor
Game::Game(string name, shared_ptr<Player> host):name{name},host{host} {
    if(name.length()<1||host.operator bool()==0) { // Operator bool ist eine Funktion von smart pointer
        throw runtime_error("");
    }
}

string Game::get_name() const {
    return name;
}

// prüfen ob beitreten möglich ist

bool Game::is_allowed(int n) const {
    int mmr = host.lock()->get_mmr();
    if(mmr*9<n*10 && mmr*11>n*10) {
        return true;
    }
    return false;
}



// durchsucht Map schaut ob spieler da ist und entfernt ihn wenn ja 
bool Game::remove_player(const GameKey& gk, shared_ptr<Player> p) {
    if(!(players.count(p->get_name()))) {return false;}
    
    players.erase(players.find(p->get_name()));
  
    return true;
}

// als erstes schauen ob erlaubt, danach einfügen in die map
bool Game::add_player(const GameKey& gk, shared_ptr<Player> p) {
    if(players.count(p->get_name())) return false;
    if(!(is_allowed(p->get_mmr()))) return false;
   
    
    players.insert({p.get()->get_name(),p});

    return true;
}

// liefret anzahl der aktiven Spieler (erreichbare weak_ptr)
size_t Game::number_of_players() const {
    int counter = 0;
    for(auto v: players){
      if(v.second.expired() == false )
      counter++;
    }
    return counter;
}


weak_ptr<Player> Game::best_player() const {
    if(number_of_players()==0) {throw runtime_error("");}
    
    auto maximum = max_element(players.begin(), players.end(), [] (const mypair a, const mypair b) {
        return a.second.lock()->get_mmr()<b.second.lock()->get_mmr();
    });
    
    return maximum->second;
}

// entfernt alle toten ptr, prüft ob i nicht kleiner als anzahl einträge oder host nicht da -> runtime error, dann winner aus neuer map 
weak_ptr<Player> Game::play(size_t i) {


    for(auto v: players){
        if(v.second.expired())
            players.erase(v.first);
    }

    if(host.expired() || players.size()<i) throw runtime_error("");

    auto it = players.begin();
    for(size_t j=0;j<i;j++){
        it++;}



    int id=0;
    for_each(players.begin(), players.end(), [&] (mypair a){
        if(i!=id){
            if(a.second.lock()->get_mmr() > it->second.lock()->get_mmr()){
                a.second.lock()->change_mmr(2*(change(false)));
            }
            else{
                a.second.lock()->change_mmr(change(false));
            }}
        id++;
    });







    it->second.lock()->change_mmr(change(true));

    return it->second;

}

ostream& Game::print(ostream& o) const {
    bool first = true;
    o << "[" << get_name() << ", " << host.lock()->get_name() << ", "<<host.lock()->get_mmr() << ", player: {";
    for(auto v: players){
        if(v.second.lock()->get_name() == get_name()) continue;
        if(first){
            o << "[" << v.second.lock()->get_name() << ", " << v.second.lock()->get_mmr()<< "]";
            first = false;

        }
        else{
            o << ", [" << v.second.lock()->get_name() << ", " << v.second.lock()->get_mmr()<< "]";

        }}
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


RGame::RGame(string s, shared_ptr<Player> p):Game(s,p) {}

int RGame::change(bool a) const {
    if(a) return 5;
    else return -5;
}


ostream& RGame::print(ostream& o) const {
    o << "Ranked Game: ";
    return Game::print(o);
}



UGame::UGame(string s,shared_ptr<Player> p):Game(s,p) {}

int UGame::change(bool a) const {
    return 0;
}

ostream& UGame::print(ostream& o) const {
    o << "Unranked Game: ";
    return Game::print(o);
}


