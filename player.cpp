#include "player.h"
#include "game.h"
#include "gamekey.h"

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

shared_ptr<Game> Player::get_hosted_game() const {
    return hosted_game;
}

void Player::change_mmr(int n) {
    mmr += n;
    if(mmr>9999) mmr =9999;
    if(mmr<0) mmr =0;
}
// error wenn s leer error, sonst Spiel starten wenn keines gestartet
bool Player::host_game(string s, Mode m) {
    if(s.empty()) throw runtime_error("");

    if(hosted_game.use_count()==0) {
      
        if(m==Mode::Ranked) {
            hosted_game = make_shared<RGame>(s,shared_from_this());
            return true;
        }

        if(m==Mode::Unranked) {
            hosted_game = make_shared<UGame>(s,shared_from_this());
            return true;
        }
    }
    return false;
}

// add player -> ja -> eintragen -> nein return false
bool Player::join_game(shared_ptr<Game> g) {
    bool cond = g->add_player((GameKey()), shared_from_this());
    if(cond){
      games.insert(make_pair(g->get_name(), g));
      return true;
    } 
    
     
    return false;
}



bool Player::leave_game(shared_ptr<Game> g) {
    games.erase(g->get_name());

    bool cond = g->remove_player(GameKey(),shared_from_this());
    return cond;
}


vector<weak_ptr<Player>> Player::invite_players(const vector<weak_ptr<Player>>& v){
    vector<weak_ptr<Player>> out;
    for(auto i: v){
        if(i.expired())
            out.push_back(i);
        else if(!(i.lock()->join_game(shared_from_this()->get_hosted_game()))) {
                out.push_back(i);
        }
    
    }
    return out;
    }



bool Player::close_game(){
    if(hosted_game.get() != nullptr){
        hosted_game.reset();
          return true;
    }
        return false;
}

ostream& Player::print(ostream& o) const {
    
    auto it = games.begin();
    if(hosted_game.get()!=nullptr) {
    o << "[" << get_name() << ", " << get_mmr() << ", hosts: " << hosted_game.get()->get_name() << ", games: {";
    for(size_t i=0;i<games.size();i++) {
        if(!it->second.expired()){
        if(i==0) {
            o << it->second.lock().get()->get_name();
        }
        else{
            o << ", " << it->second.lock().get()->get_name();
        }
        }
        it++;
    }
    o << "}]";
    }
    else{
    o << "[" << get_name() << ", " << get_mmr() << ", " << "hosts: nothing" << ", games: {";
    for(size_t i=0;i<games.size();i++) {
        if(!it->second.expired()){
            if(i==0){
                o << it->second.lock().get()->get_name();
            }
            else{
                o << ", " << it->second.lock().get()->get_name();
            }
        }
        it++;
    }
    o << "}]";
    }
    
    return o;
}

ostream& operator<<(ostream& o, Player p) {
    return p.print(o);
}
