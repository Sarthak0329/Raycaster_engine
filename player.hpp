#ifndef _PLAYER_H
#define _PLAYER_H
#include <SFML/Graphics/RenderTarget.hpp>

class Player{

public:
  void draw(sf::RenderTarget &target);
  void update(float deltaTime);
  //define player position and orientation
  sf::Vector2f position;
  float angle;

};

#endif // !_PLAYER_H
