#include <iostream>
#include "grid.hpp"

Tile& Grid::get_tile_at_position(int column_index, int row_index)
{
    return tiles[row_index][column_index];
}

void Grid::print() const
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

int Grid::get_column_count() const 
{
    return column_count;
}

int Grid::get_row_count() const 
{
    return row_count;
}
