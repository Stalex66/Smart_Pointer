#include "player.h"
#include "game.h"
using namespace std;

Player::Player(string name,int mmr):name{name},mmr{mmr}{
    if(name.empty() || mmr <0 || mmr>9999) throw runtime_error("Player Konsturktor");
}

string Player::get_name() const {
    return name;
}

int Player::get_mmr() const{
    return mmr;
}

shared_ptr<Game> Player::get_hosted_game() const{
    if(hosted_game != nullptr){return hosted_game;}
    else return nullptr;

}

void Player::change_mmr(int n){
    if(mmr+n>-1 && mmr+n <10000 ){
        mmr += n;
    }
}

bool Player::host_game(string s, Mode m){ // game erzeugen noch implementieren
    if(s.empty()) throw runtime_error("host_game");
    if(hosted_game != nullptr) return false;
    else{
        if(m ==Mode::Ranked){
            auto game = RGame(s,shared_ptr<Player>(this));
        }
        else{
            auto game = UGame(s,shared_ptr<Player>(this));
        }

    }
    return true;
}

bool Player::join_game(shared_ptr <Game> g){
    bool help = g->add_player()

}