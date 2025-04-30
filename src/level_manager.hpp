#pragma once

#include "tile.hpp"
#include "grid.hpp"
#include "level.hpp"
#include <vector>

struct LevelManager 
{
    // CONSTRUCTORS ---
    LevelManager(const std::string& filepath);

    // PUBLIC FUNCTIONS ---
    void print_all_levels() const;

    // TODO: Remove this after we read in the levels
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

    private:
    // PRIVATE FUNCTIONS ---
    void read_from_config_file(const std::string& filepath);

    // PRIVATE PROPERTIES ---
    std::vector<Level> all_levels;
};