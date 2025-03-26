#pragma once

#include <vector>
#include "tile.hpp"

// Represents a grid of tiles to use in our game.
struct Grid
{
    const void print();
    const Tile& getTileAtPosition(int column_index, int row_index);

    // Creates a grid with matching width and height.
    // @param width The max number of tiles in a row. 
    // @param height The max number of tile rows.
    Grid(int width, int height): column_count(width), row_count(height) 
    {
        // Create the full grid of tiles
        for (int i = 0; i < width * height; i++)
        {
            tiles.emplace_back(Tile{ TileType::FLOOR, i == 0 });
        }
    }

    private:

    int column_count;
    int row_count;

    std::vector<Tile> tiles;
};