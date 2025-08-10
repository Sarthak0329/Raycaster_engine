#ifndef _RENDER_H
#define _RENDER_H
#include "player.hpp"
#include "map.hpp"
#include <SFML/Graphics.hpp>

constexpr float SCREEN_W = 1200.0f;
constexpr float SCREEN_H = 675.0f;

class Renderer{
public:
 void drawRays(sf::RenderTarget &target,const Player &player,const Map &map);
 void draw3DView(sf::RenderTarget &target,const Player &player,const Map &map);


private:
 

};


#endif // !_RENDER_H

