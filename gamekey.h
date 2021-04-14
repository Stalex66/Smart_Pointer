//
class Game;
class GameKey{

GameKey() {}
friend bool Player::join_game(std::shared_ptr<Game>);
friend bool Player::leave_game(std::std_ptr<Game>);

};
