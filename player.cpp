#include "player.h"
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
    if(hosted_game.use_count() == 0) return false;
    else{
        if(m ==Mode::Ranked){
            hosted_game = RGame(s,shared_ptr<Player>(this));
        }
        else{
            hosted_game = UGame(s,shared_ptr<Player>(this));
        }

    }
    return true;
}

bool Player::join_game(shared_ptr <Game> g){
    bool cond = (g.get()->add_player(GameKey(),shared_from_this())) // statt get mal derefenzieren probieren bitte
        if(cond){
        games.insert({g.get()->get_name(),g});
            return true;}
        else
            return false;

}

bool Player::leave_game(shared_ptr <Game> g) {
    bool cond1 = (find(games.begin(),games.end(),g.get()->get_name()) != games.end());
    games.erase(g.get()->get_name());
    bool cond2 = (g.get()->remove_player(GameKey(),shared_from_this()));

    if(cond1 && cond2)
        return true;
    else
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
    return out;
    }

    }

bool Player::close_game(){
    if(hosted_game.get != nullptr){
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
