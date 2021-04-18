//
//  game.cpp
//  Gaming_Platform
//
//  Created by Christoph Loik on 15.04.21.
//

#include "game.h"
#include <algorithm>



Game::Game(string name, shared_ptr<Player> host):name{name},host{host} {
    if(name.length()<1||host.operator bool()==0) {
        throw runtime_error("");
    }
}

string Game::get_name() const {
    return name;
}


bool Game::is_allowed(int n) const {
    int mmr = host.lock().get()->get_mmr();
    if(n*0.9<mmr&&n*1.1>mmr) {
        return true;
    }
    return false;
}

// GameKey kann nur von Player::join_game() und Player::leave_game() aufgerufen werden, daher kann remove/add_player() nur von den in GameKey als friend markierten methoden aufgerufen werden, und somit kommt es zu keiner inkonsitenz beim hinzufügen/löschen von playern
bool Game::remove_player(const GameKey& gk, shared_ptr<Player> p) {
    if(players.find(p->get_name())==players.end()) {return false;}
    
    players.erase(players.find(p->get_name()));
  
    return true;
}


bool Game::add_player(const GameKey& gk, shared_ptr<Player> p) {
    
    if(!is_allowed(p.get()->get_mmr())||players.find(p.get()->get_name())!=players.end()) {
        return false;
    }
    
    players.insert({p.get()->get_name(),p});
    return true;
}


using pairtype = pair<string,weak_ptr<Player>>;
weak_ptr<Player> Game::best_player() const {
    if(players.size()==0) {throw runtime_error("");}
    
    auto it = max_element(players.begin(), players.end(), [&] (const pairtype& p1, const pairtype& p2) {
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


