#include <iostream>
#include "grid.hpp"

const Tile& Grid::getTileAtPosition(int column_index, int row_index) 
{
    int tile_index = column_index + (row_index * column_count);
    return tiles[tile_index];
}

const void Grid::print()
{
    std::cout << "Printing Grid...\n";
    for (int i = 0; i < tiles.size(); i++)
    {
        // Map from i to (row_index, column_index) coordinates so we can print better
        int column_index = i % column_count;
        int row_index = i / row_count;

        std::cout << "(" << column_index << " , " << row_index << "): ";
        tiles[i].print();
    }
}
