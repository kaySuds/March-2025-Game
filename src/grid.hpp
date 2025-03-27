#pragma once

#include <vector>
#include "tile.hpp"

// Represents a grid of tiles to use in our game.
struct Grid
{
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
                TileType type = TileType::FLOOR;
                if (row_index == 0) 
                {
                    type = TileType::HOLE;
                }
                Tile newTile = Tile{ type, column_index == 2 };
                newTile.set_edge_type_for_edge(TileEdge::TOP, TileEdgeType::WALL);
                newTile.set_edge_type_for_edge(TileEdge::LEFT, TileEdgeType::DOOR);
                row.emplace_back(newTile);
            }
            tiles.emplace_back(row);
        }
    }
    
    void print() const;

    const Tile& get_tile_at_position(int column_index, int row_index) const;

    int get_column_count() const;
    int get_row_count() const;

    private:

    int column_count;
    int row_count;

    // 2D Vector of tiles
    std::vector<std::vector<Tile>> tiles;
};