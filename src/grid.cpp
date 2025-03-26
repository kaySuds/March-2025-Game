#include <iostream>
#include "grid.hpp"

const Tile& Grid::getTileAtPosition(int column_index, int row_index) 
{
    return tiles[row_index][column_index];
}

const void Grid::print()
{
    std::cout << "Printing Grid...\n";

    for (int row_index = 0; row_index < row_count; row_index++) 
    {
        for(int column_index = 0; column_index < column_count; column_index++) 
        {
            std::cout << "Column: " << column_index << " , Row: " << row_index << " "; // No newline because tile print will have it
            tiles[row_index][column_index].print();
        }
    }
}
