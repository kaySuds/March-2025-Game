#pragma once

#include "tile.hpp"
#include <vector>

struct LevelManager 
{
    std::vector<std::vector<Tile>> level_one {
        { 
            { TileType::HOLE, TileEdgeType::WALL, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::WALL },
            { TileType::FLOOR, TileEdgeType::WALL, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN },
            { TileType::HOLE, TileEdgeType::WALL, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN },
            { TileType::FLOOR, TileEdgeType::WALL, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN },
            { TileType::FLOOR, TileEdgeType::WALL, TileEdgeType::WALL, TileEdgeType::OPEN, TileEdgeType::OPEN },
        },
        {
            { TileType::HOLE, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::WALL },
            { TileType::FLOOR, TileEdgeType::OPEN, TileEdgeType::WALL, TileEdgeType::OPEN, TileEdgeType::WALL },
            { TileType::FLOOR, TileEdgeType::OPEN, TileEdgeType::WALL, TileEdgeType::OPEN, TileEdgeType::OPEN },
            { TileType::FLOOR, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::WALL },
            { TileType::FLOOR, TileEdgeType::OPEN, TileEdgeType::WALL, TileEdgeType::OPEN, TileEdgeType::WALL },
        },
        {
            { TileType::FLOOR, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::WALL },
            { TileType::FLOOR, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN },
            { TileType::FLOOR, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN },
            { TileType::LADDER, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN },
            { TileType::FLOOR, TileEdgeType::OPEN, TileEdgeType::WALL, TileEdgeType::OPEN, TileEdgeType::OPEN },
        },
        {
            { TileType::FLOOR, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::WALL },
            { TileType::HOLE, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN },
            { TileType::HOLE, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN },
            { TileType::FLOOR, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::OPEN },
            { TileType::FLOOR, TileEdgeType::OPEN, TileEdgeType::WALL, TileEdgeType::OPEN, TileEdgeType::OPEN },
        },
        {
            { TileType::FLOOR, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::WALL, TileEdgeType::WALL },
            { TileType::FLOOR, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::WALL, TileEdgeType::OPEN },
            { TileType::FLOOR, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::WALL, TileEdgeType::OPEN },
            { TileType::FLOOR, TileEdgeType::OPEN, TileEdgeType::OPEN, TileEdgeType::WALL, TileEdgeType::OPEN },
            { TileType::FLOOR, TileEdgeType::OPEN, TileEdgeType::WALL, TileEdgeType::WALL, TileEdgeType::OPEN },
        }
    };
};