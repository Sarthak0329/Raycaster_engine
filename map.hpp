#ifndef _MAP_H
#define _MAP_H
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>

class Map {
public:

 Map(float cellSize,int width,int height);
 Map(float _cellSize,std::vector<std::vector<int>> _grid);//we will use this constructor
                                                        // to make our own custom map !!
 void draw(sf::RenderTarget &target);

 const std::vector<std::vector<int>> &getGrid() const;
 float getCellSize() const;

private:
  std::vector<std::vector<int>> grid;
  float cellSize;
};

 
 #endif // !_MAP_H
 
