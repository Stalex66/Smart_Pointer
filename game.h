#include <iostream>
#include <memory>
#include <string>
#include <map>

class Game{
  string name;
  weak_ptr<Player> host;
  map<string,weak_ptr<Player>> players;
public:
  Game(string name,shared_ptr<Player>host;);
  string get_nmame const();
  bool is_allowed(int n) const;
  bool remove_player(const GameKey& gk, shared_ptr<Player> p);
  bool add_player(const GameKey& gk, shared_ptr<Player> p);
  weak_ptr<Player> best_player() const;
  size_t number_of_players() const;
  virtual int change(bool) const = 0;
  weak_ptr<Player> play(size_t i);
  virtual ~Game() = default;
  virtual ostream& print(ostream& o)const;
  friend ostream& operator<<(ostream& o, Game a);
};

class UGame: public Game{
  RGame(string,shared_ptr<Player>);
  int change(bool won) const;
  ostream& print(ostream& o)const;
};

class UGame: public game{
  UGame(string,shared_ptr<Player>);
  int change(bool) const;
  ostream& print(ostream& o)const;

};
