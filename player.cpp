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
    if(mmr>9999) {
        mmr = 9999;
    }
    if(mmr<0) {
        mmr =0;
    }
}

bool Player::host_game(string s, Mode m) {
    if(s.size()==0) {
        throw runtime_error("");
    }
    if(hosted_game.use_count()==0) {
        if(m==Mode::Ranked) {
            auto p = make_shared<RGame>(s,shared_from_this());
            hosted_game=p;
        }
        if(m==Mode::Unranked) {
            auto p = make_shared<UGame>(s,shared_from_this());
            hosted_game=p;
        }
        return true;
    }
    return false;
}


bool Player::join_game(shared_ptr<Game> g) {
    
    
    if(g.get()->add_player(GameKey(),shared_from_this())) {
        games.insert({g.get()->get_name(),g});
        return true;
    };
     
    return false;
}

bool Player::leave_game(shared_ptr<Game> g) {
    
    // check ob erfolgreich?
    games.erase(g.get()->get_name());
    if(g.get()->remove_player(GameKey(),shared_from_this())) {
        return true;
    };
    
    return false;


}
vector<weak_ptr<Player>> Player::invite_players(const vector<weak_ptr<Player>>& v){
    vector<weak_ptr<Player>> out;
    for(auto i: v){
        if(i.expired())
            out.push_back(i);
        else {
            if(!(i.lock().get()->join_game(shared_from_this().get()->get_hosted_game()))) // lock.get evtl ändern
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

ostream& Player::print(ostream& o) const { // KOPIE!!!!

    auto it = games.begin();
    if(hosted_game.get()!=nullptr) {
        o << "[" << get_name() << " ," << get_mmr() << ", " << hosted_game.get()->get_name() << ", games: {";
        for(size_t i=0;i<games.size();i++) {
            if((i+1)<games.size()) {
                o << it->second.lock().get()->get_name() << ", ";
            }
            else{
                o << it->second.lock().get()->get_name();
            }
            it++;
        }
        o << "}]";
    }
    else{
        o << "[" << get_name() << " ," << get_mmr() << ", " << "nothing" << ", games: {";
        for(size_t i=0;i<games.size();i++) {
            if(!it->second.expired()){ // so richtig? --> games sind nach close ja noch immer in der map (werden nicht removed)
                if((i+1)<games.size()) {
                    o << it->second.lock().get()->get_name() << ", ";
                }
                else{
                    o << it->second.lock().get()->get_name();
                }
            }
            it++;
        }
        o << "}]";
    }

    return o;
}

ostream& operator<<(ostream& o, Player p) {// KOPIE!!!!
    return p.print(o);
}
