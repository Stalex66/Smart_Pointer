//
//  main.cpp
//  Gaming_Platform
//
//  Created by Christoph Loik on 15.04.21.
//

#include <iostream>
#include <string>
#include "player.cpp"
#include "game.cpp"




using namespace std;


int main(int argc, const char * argv[]) {


#define WRK(cond) std::cout << (cond ? "\n worked \n" : "\n ERROR \n");

// Konstruktor::
try{
shared_ptr<Player> ptr1 = make_shared<Player>("Alex",1000);
}
catch(runtime_error x){
  cout << "1. worked";
}
try{
shared_ptr<Player> ptr2 = make_shared<Player>("Alex",-10);
}
catch(runtime_error u){
  cout << "1. worked";
}

// echter Test


// create Dead Pointer

std::weak_ptr<Player> dead1;
std::weak_ptr<Player> dead2;
for(size_t i=0; i<1;i++){
  shared_ptr<Player> Dark = make_shared<Player>("Darkterminator",100);
  dead1 = Dark;
  shared_ptr<Player> Darker = make_shared<Player>("Darkterminator",0);
  dead2 = Darker;
}


//


shared_ptr<Player> alex = make_shared<Player>("Alex",100);
shared_ptr<Player> klaus = make_shared<Player>("Klaus",100);
shared_ptr<Player> dieter= make_shared<Player>("Dieter",100);
shared_ptr<Player> christoph = make_shared<Player>("Christoph",100);
std::weak_ptr<Player> dieter_weak = std::weak_ptr<Player>(dieter);
std::weak_ptr<Player> klaus_weak = std::weak_ptr<Player>(klaus);
std::weak_ptr<Player> christoph_weak = std::weak_ptr<Player>(christoph);
std::weak_ptr<Player> alex_weak = std::weak_ptr<Player>(alex);
vector<weak_ptr<Player>> list{dead1,dead2,klaus_weak,dieter_weak};

cout << "\n ---Player \n";
WRK(alex->host_game("Dota2", Mode::Ranked) == true);
WRK(christoph->host_game("CIV6", Mode::Unranked) == true);
WRK(alex->host_game("Dota2", Mode::Ranked) == false);
WRK(alex->get_name() == "Alex");
WRK(alex->get_mmr() == 100);
WRK(alex->get_hosted_game().use_count() != 0);
WRK(christoph->join_game(alex->get_hosted_game())); // hier gibt es ein problem
WRK(alex->join_game(christoph->get_hosted_game()));
WRK(alex->close_game());
/*WRK(christoph->invite_players(list).size() ==2);
vector<weak_ptr<Player>> list2{christoph,alex};
vector<weak_ptr<Player>> testung = christoph->invite_players(list2);
for_each(testung.begin(),testung.end(),[&](weak_ptr<Player> a){
        cout << a.lock()->get_name();
       
    });*/
cout << *alex <<"\n";
cout << *christoph << "\n";
WRK(alex->close_game() == false);
WRK(christoph->close_game() == true);

cout << "\n ---Game \n";
alex->host_game("Dota2", Mode::Ranked);
auto dota = alex->get_hosted_game();
WRK(alex->get_name() = "Alex");
WRK(dota->is_allowed(100) == true);
//WRK(dota->number_of_players() == 1);
//weak_ptr<Player> pruf = dota->best_player(); // error weil leer??
//WRK(pruf.lock()->get_name() == "Alex");















}







