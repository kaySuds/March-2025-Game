#pragma once

#include <string>
#include <vector>
#include "tile.hpp"

struct Level
{
    std::string name;
    int start_position_x;
    int start_position_y;
    std::vector<std::vector<Tile>> tile_grid;
};