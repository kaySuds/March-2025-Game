#pragma once

#include <vector>
#include "tile.hpp"

// Represents a grid of tiles use to represents the world in our game.
struct Grid
{
    const void print();
    const Tile& getTileAtPosition(int column_index, int row_index);

    Grid(int t_size, int width, int height): tile_size(t_size), column_count(width), row_count(height) 
    {
        // Create the full grid of tiles
        for (int i = 0; i < width * height; i++)
        {
            tiles.emplace_back(Tile{ TileType::FLOOR, i == 0 });
        }
    }

    private:

    int tile_size;
    int column_count;
    int row_count;

    std::vector<Tile> tiles;
};