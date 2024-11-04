#include "map.hpp"

bool Map::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height) 
{
  // Load the tileset texture
  if (!mTileset.loadFromFile(tileset)) 
  {
    return false; // Return false if texture loading fails
  }

  // Resize the vertex array to fit the level size
  mVertices.setPrimitiveType(sf::Quads);
  mVertices.resize(width * height * 4); // 4 vertices per tile (quad)

  // Populate the vertex array with rectangles (quads) per tile
  for (unsigned int i = 0; i < width; ++i) 
  {
    for (unsigned int j = 0; j < height; ++j) 
    {
      // Get the current tile number
      int tileNumber = tiles[i + j * width];

      // Find its position in the tileset texture
      int tu = tileNumber % (mTileset.getSize().x / tileSize.x);
      int tv = tileNumber / (mTileset.getSize().x / tileSize.x);

      // Get a pointer to the quad's vertices of the current tile
      sf::Vertex* tile = &mVertices[(i + j * width) * 4];

      // Define the 4 corners of the quad
      tile[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
      tile[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
      tile[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
      tile[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

      // Define the texture coordinates (IntRect) for the quad
      tile[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
      tile[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
      tile[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
      tile[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
    }
  }
  return true; // Return true indicating successful loading
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // apply the transform
  states.transform *= getTransform();

  // apply the tileset texture
  states.texture = &mTileset;

  // draw the vertex array
  target.draw(mVertices, states);
}
