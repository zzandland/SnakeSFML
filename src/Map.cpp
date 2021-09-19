#include "Map.hpp"

Map::Map(int w, int h) {
  this->w = w;
  this->h = h;
  dirt = TextureManager::load("assets/dirt.png");
  grass = TextureManager::load("assets/grass.png");
  water = TextureManager::load("assets/water.png");

  map.resize(h, std::vector<Tile>(w, Tile::kDirt));
}

void Map::load(const char *path) {
  std::ifstream ifs(path);
  char c;
  if (!ifs.is_open()) {
    std::cerr << "Could not open the file - '" << path << "'" << std::endl;
  }

  int y, x;
  y = x = 0;
  while (ifs.get(c)) {
    if (c == '\n') {
      ++y;
      x = 0;
    } else {
      Tile t = static_cast<Tile>(c - '0');
      map[y][x++] = t;
    }
  }

  ifs.close();
}

void Map::draw() {
  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      Tile t = map[y][x];
      switch (t) {
        case Tile::kDirt:
          TextureManager::draw(dirt, srcRect, destRect);
          break;
        case Tile::kGrass:
          TextureManager::draw(grass, srcRect, destRect);
          break;
        case Tile::kWater:
          TextureManager::draw(water, srcRect, destRect);
          break;
      }
    }
  }
}