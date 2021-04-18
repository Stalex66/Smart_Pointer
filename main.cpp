//
//  main.cpp
//  Gaming_Platform
//
//  Created by Christoph Loik on 15.04.21.
//

#include <iostream>
#include <string>
#include "player.h"




using namespace std;


int main(int argc, const char * argv[]) {
    

    
    
    shared_ptr<Player> ptr1 = make_shared<Player>("Hans",400);
    shared_ptr<Player> ptr2 = make_shared<Player>("Sepp",401);
    shared_ptr<Player> ptr3 = make_shared<Player>("Christoph",399);
    
    ptr1.get()->host_game("Hosted_1", Mode::Ranked);
    ptr2.get()->host_game("Hosted_2", Mode::Unranked);
    
    
    vector<weak_ptr<Player>> testlist;
    testlist.push_back(ptr2);
    testlist.push_back(ptr3);
    

    
      ptr3.get()->join_game(ptr1.get()->get_hosted_game());
      ptr3.get()->join_game(ptr1.get()->get_hosted_game());
      ptr2.get()->join_game(ptr1.get()->get_hosted_game());
    
      ptr3.get()->join_game(ptr1.get()->get_hosted_game());
    
//     ptr3.get()->leave_game(ptr2.get()->get_hosted_game()); // geht
     ptr1.get()->change_mmr(100); // geht

//    ptr1.get()->close_game();
    
    cout << *(ptr1.get()->get_hosted_game()->best_player().lock().get()) << "\n\n\n";
    
    cout << *(ptr1.get()->get_hosted_game().get()->play(0).lock().get()) << "!!\n\n";
    
 //   cout << *(ptr1.get()->get_hosted_game()->best_player().lock().get()) << "\n\n\n";
    
    ptr1.get()->invite_players(testlist);
    ptr2.get()->invite_players(testlist);
//    ptr3.get()->invite_players(testlist); // geht nicht weil ptr3 kein host ist, muss man das checken?

    cout << *ptr1 << "\n";
    cout << *ptr2 << "\n";
    cout << *ptr3 << "\n";
    

    return 0;
}

