#include <unordered_map>
#include <cmath>
#include "Boid.h"

struct SpatialGrid {
    static constexpr float CELL = COHESION_RADIUS;

    std::unordered_map<int, std::vector<int>> cells;  // cell_id → boid indices


    int key(int cx, int cy) const {
        return cx * 10000 + cy;
    }

    int cellX(float x) const { return int(std::floor(x / CELL)); }
    int cellY(float y) const { return int(std::floor(y / CELL)); }

    void build(const std::array<Boid, NUM_BOIDS>& boids) {
        cells.clear();
        for (int i = 0; i < int(boids.size()); ++i) {
            int cx = cellX(boids[i].pos.x);
            int cy = cellY(boids[i].pos.y);
            cells[key(cx, cy)].push_back(i);
        }
    }


    std::vector<int> query(float x, float y) const {
        std::vector<int> result;
        int cx = cellX(x), cy = cellY(y);
        for (int dx = -1; dx <= 1; ++dx)
            for (int dy = -1; dy <= 1; ++dy) {
                auto it = cells.find(key(cx + dx, cy + dy));
                if (it != cells.end())
                    for (int idx : it->second)
                        result.push_back(idx);
            }
        return result;
    }
};
