#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Clock.hpp>
#include "player.hpp"
#include "map.hpp"
#include "renderer.hpp"

int main(){
  sf::RenderWindow window(sf::VideoMode(SCREEN_W,SCREEN_H),"Raycaster",sf::Style::Close | sf::Style::Titlebar);

    
   std::vector<std::vector<int>> grid ={
    {1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,1,0,0,0,1,0,1},
    {1,0,0,0,0,1,0,0,0,1,0,1},
    {1,0,1,0,0,1,0,0,0,1,0,1},
    {1,0,0,0,0,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,0,0,0,0,0,1,1},
    {1,0,0,0,0,0,0,0,0,0,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1}
  };

   Map map(20.0f,grid);
    Renderer renderer;  
    Player player;
    player.position= sf::Vector2f(150.0,150.0f);
    sf::RectangleShape floor(sf::Vector2f(SCREEN_W,SCREEN_H));
    floor.setPosition(0,SCREEN_H / 2);
    floor.setFillColor(sf::Color(124,252,0));

    sf::RectangleShape sky(sf::Vector2f(SCREEN_W,SCREEN_H));
    sky.setPosition(0,0);
    sky.setFillColor(sf::Color(135,206,235));




    sf::Clock gameClock;

    while(window.isOpen())
    {
      float deltaTime = gameClock.restart().asSeconds();//when the restart function is 
                                                        //is invoked upon the sf::class variable
                                                        //it returns the total time elapsed since it start 
                                                        //and then again set back to zero 
      sf::Event event;
      while(window.pollEvent(event))
      {
        if(event.type == sf::Event::Closed)
        {
          window.close();

        }
        else if (event.key.code == sf::Keyboard::Escape) {
          window.close();
        }
      }
      player.update(deltaTime);//update the player properties

      window.clear();
      window.draw(sky);

      window.draw(floor);

      renderer.draw3DView(window,player,map);

      map.draw(window);
      

      map.draw(window);


      renderer.drawRays(window,player,map);
      player.draw(window);


      window.display();

    }
    return 0;
}

