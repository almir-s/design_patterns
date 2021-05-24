#include <iostream>
#include <memory>

enum class TerrainEnum : uint8_t { TERRAIN_GRASS, TERRAIN_HILL, TERRAIN_RIVER };

const int width = 100;
const int height = 100;

// NON pattern version:
class World {
  public:
  World(int x, int y) {
    std::cout << "Generate World" << std::endl;
    tiles_[x][y] = TerrainEnum::TERRAIN_GRASS;
  }
  int getMovementCost(int x, int y) const {
    switch (tiles_[x][y]) {
      case TerrainEnum::TERRAIN_GRASS:
        return 1;
      case TerrainEnum::TERRAIN_HILL:
        return 2;
      case TerrainEnum::TERRAIN_RIVER:
        return 3;
      default:
        return 0;
    }
  }

  bool isWater(int x, int y) const {
    switch (tiles_[x][y]) {
      case TerrainEnum::TERRAIN_GRASS:
        return false;
      case TerrainEnum::TERRAIN_HILL:
        return false;
      case TerrainEnum::TERRAIN_RIVER:
        return true;
      default:
        return false;
    }
  }

  private:
  TerrainEnum tiles_[width][height];
};

//

// FLYWEIGHT PATTERN:

class Terrain {
  public:
  Terrain(int movementCost, bool isWater)
      : movementCost_{movementCost}, isWater_{isWater} {
  }
  int getMovementCost() const { return movementCost_; }
  bool isWater() const { return isWater_; }

  private:
  int movementCost_;
  bool isWater_;
};

class OptimizedWorld {
  public:
  OptimizedWorld()
      : grassTerrain_{1, false},
        riverTerrain_{3, true},
        hillTerrain_{2, false} {
    tiles_[0][0] = &grassTerrain_;
  }

  void generateTerrain() {
    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        // Sprinkle some hills.
        if (std::rand() / 2 == 0) {
          tiles_[x][y] = &hillTerrain_;
        } else {
          tiles_[x][y] = &grassTerrain_;
        }
      }
    }

    // Lay a river.
    int x = rand() % 100;
    for (int y = 0; y < height; y++) {
      tiles_[x][y] = &riverTerrain_;
    }
  }

  const Terrain& getTile(int x, int y) const { return *tiles_[x][y]; }

  private:
  Terrain grassTerrain_;
  Terrain riverTerrain_;
  Terrain hillTerrain_;

  Terrain* tiles_[width][height];
};

int main() {
  std::cout << "Flyweight pattern" << std::endl;
  World world(0, 1);
  std::cout << "Is watter: " << world.isWater(0, 1) << std::endl;

  // Optimized version:
  OptimizedWorld optimzedWorld;
  optimzedWorld.generateTerrain();
  int cost = optimzedWorld.getTile(50, 50).getMovementCost();
  std::cout << "Movement cost: " << cost << std::endl;
  return 0;
}
