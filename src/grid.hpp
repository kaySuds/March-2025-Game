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
    Grid(int columns, int rows): column_count(columns), row_count(rows) 
    {
        // Vector "for loop" to set up the tiles
        for (int row_index = 0; row_index < rows; row_index++) 
        {
            //define row
            std::vector<Tile> row;
            for (int column_index = 0; column_index < columns; column_index++)
            {
                row.emplace_back(Tile{ TileType::FLOOR, true });
            }
            tiles.emplace_back(row);
        }
    }

    private:

    int column_count;
    int row_count;

    // 2D Vector of tiles
    std::vector<std::vector<Tile>> tiles;
};