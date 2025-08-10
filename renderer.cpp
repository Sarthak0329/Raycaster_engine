#include "renderer.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstddef>
#include <climits>

constexpr float PI = 3.141592653589793f;
constexpr size_t MAX_RAYCASTING_STEPS = 16;
constexpr float PLAYER_FOV = 60.0f;
constexpr size_t NUM_RAYS = 400;
constexpr float COLUMN_WIDTH = SCREEN_W / (float)NUM_RAYS;

struct Ray {

  sf::Vector2f hitPosition;
  float distance;
  bool hit;
  bool isHitVertical;
};

static Ray castRay(sf::Vector2f start,float angleInDegrees,const Map &map);

 void Renderer::draw3DView(sf::RenderTarget &target,const Player &player,const Map &map){

  float angle = player.angle - PLAYER_FOV / 2.0f;
  float angleIncrement = PLAYER_FOV / (float)NUM_RAYS;

 for (size_t i = 0; i < NUM_RAYS; i++,angle += angleIncrement) {
 
 Ray ray = castRay(player.position,angle,map);
  if(ray.hit){
      
      ray.distance *= std::cos((player.angle - angle) * PI/180.0f);//ray.distance is basically the perpendicular distance from the wall to the player
      float shade = ray.isHitVertical ? 0.8f : 1.0f;
      float wallHeight = (map.getCellSize()* SCREEN_H) / ray.distance + 80.0f;
      sf::RectangleShape column(sf::Vector2f(COLUMN_WIDTH,wallHeight));
      column.setFillColor(sf::Color(255*shade,255*shade,255*shade));

      float wallOffset = (float)((SCREEN_H - wallHeight)/2);
      column.setPosition(i*COLUMN_WIDTH,wallOffset);
      target.draw(column);


   }
  }
 


 }



 void Renderer::drawRays(sf::RenderTarget &target,const Player &player,const Map &map){

 for (float angle = player.angle - PLAYER_FOV / 2.0f;angle < player.angle + PLAYER_FOV / 2; angle += 0.1f) {
 
 Ray ray = castRay(player.position,angle,map);

 if(ray.hit){
  sf::Vertex line[]{
      sf::Vertex(player.position),
      sf::Vertex(ray.hitPosition),
   };

  target.draw(line,2,sf::Lines);
   }
  }
 }


//Function to cast rays;implementing the ray drawing algorithm !!
Ray castRay(sf::Vector2f start,float angleInDegrees,const Map &map)
{
  float angle = angleInDegrees * PI /180.0f;

  float vTan = -std::tan(angle);
  float hTan = -1.0f/std::tan(angle);

  const auto &grid = map.getGrid();

  float cellSize = map.getCellSize();

  sf::Vector2f vrayPos,hrayPos,offset;
  size_t vdof = 0,hdof = 0;
  float vdist = std::numeric_limits<float>::max(),hdist = std::numeric_limits<float>::max();
  bool hit = false;


  //for vertical wall hit !!
  
  //ray facing right
  
  if (std::cos(angle) > 0.001f) {
    vrayPos.x = std::floor(start.x / cellSize) * cellSize + cellSize;
    vrayPos.y = (start.x - vrayPos.x) * vTan + start.y;
    offset.x =  cellSize;
    offset.y =  -offset.x * vTan;
  }
  //for ray facing left
  else if (std::cos(angle) < -0.001f) {
    vrayPos.x = std::floor(start.x / cellSize) * cellSize - 0.01f;
    vrayPos.y = (start.x - vrayPos.x) * vTan + start.y;
    offset.x = -cellSize;
    offset.y = -offset.x * vTan;
  }
 //for a ray perfectly facing right or left 
  else{
    vdof = MAX_RAYCASTING_STEPS;
  }

  

  for (; vdof < MAX_RAYCASTING_STEPS; vdof++) {
    int mapX = (int)(vrayPos.x/ cellSize);
    int mapY = (int)(vrayPos.y/ cellSize);

   if(mapY < grid.size() && mapX < grid[mapY].size() && grid[mapY][mapX])
    //if(grid[mapX][mapY])
    {
      hit = true;
      vdist = std::sqrt((vrayPos.x - start.x)* (vrayPos.x - start.x) +
              (vrayPos.y - start.y)* (vrayPos.y - start.y));
      break;
    }
    vrayPos += offset;
  }

    //horizontal ray collision 
    //for ray facing up
  if (std::sin(angle) > 0.001f) {
    hrayPos.y = std::floor(start.y / cellSize) * cellSize + cellSize;
    hrayPos.x = (start.y - hrayPos.y)* hTan + start.x;
    offset.y =  cellSize;
    offset.x = -offset.y * hTan;
  }
  //for ray facing down
  else if (std::sin(angle) < -0.001f) {
    hrayPos.y = std::floor(start.y / cellSize) * cellSize - 0.01f;
    hrayPos.x = (start.y - hrayPos.y) * hTan + start.x;
    offset.y = -cellSize;
    offset.x = -offset.y * hTan;
  }
 //for a ray perfectly facing right or left 
  else{
    hdof = MAX_RAYCASTING_STEPS;
  }

  
  for (; hdof < MAX_RAYCASTING_STEPS; hdof++) {
    int mapX = (int)(hrayPos.x/ cellSize);
    int mapY = (int)(hrayPos.y/ cellSize);

   if(mapY < grid.size() && mapX < grid[mapY].size() && grid[mapY][mapX])
    
    { 
      hit = true;
      hdist = std::sqrt((hrayPos.x - start.x)* (hrayPos.x - start.x) +
                        (hrayPos.y - start.y)* (hrayPos.y - start.y));
      
      break;
    }
    hrayPos += offset;
  }

return Ray{hdist < vdist ? hrayPos : vrayPos,std::min(hdist,vdist),hit,vdist < hdist};
}
