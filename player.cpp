#include "player.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

constexpr float PI = 3.141592653589793f;
constexpr float TURN_SPEED = 100.0f;
constexpr float MOVE_SPEED = 100.0f;


void Player::draw(sf::RenderTarget &target){
  
  sf::CircleShape circle(7.0f);
  circle.setFillColor(sf::Color::Blue);
  circle.setPosition(position);
  circle.setOrigin(circle.getRadius(),circle.getRadius());

  
 target.draw(circle);

}

void Player::update(float deltaTime)
{

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
     angle -= TURN_SPEED * deltaTime;  

  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){

    angle += TURN_SPEED * deltaTime;      
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){

    float radian = angle * PI / 180.0f;
    position.x += cos(radian)*MOVE_SPEED*deltaTime;
    position.y += sin(radian)*MOVE_SPEED*deltaTime;
    
  }

}
