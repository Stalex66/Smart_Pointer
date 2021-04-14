#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <vector>
using namespace std;

class Player{
  string name;
  int mmr;
  shared_ptr<Game>hosted_game;
  map<string,weak_ptr<Game>> games;

public:

  Player(string name,intr mmr);
  string get_name() const;
  int get_mmr() const;
  shared_ptr<Game> get_hosted_game() const;
  void change_mmr(int n);
  bool host_game(string s, Mode m);
  bool join_game(shared_ptr<Game> g);
  bool leave_game(shared_ptr<Game> g);
  vector<weak_ptr<Player>> invite_players(const vector<weak_ptr<Player>>& v);
  bool close_game();
  ostream& print(ostream& o) const;
  friend ostream& operator<<(ostream& o, Player a);

};
