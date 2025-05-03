#include "level_manager.hpp"
#include <fstream>
#include <iostream>
#include "level.hpp"

// HELPERS ---

// Returns the matching tile type for the given abbreviation. Defaults to FLOOR.
TileType get_tile_type_by_abbreviation(const std::string& abbreviation)
{  
    if (abbreviation == "OBJ")
    {
        return TileType::FLOOR_WITH_OBJECT;
    }
    if (abbreviation == "LDR")
    {
        return TileType::LADDER;
    }
    if (abbreviation == "HLE")
    {
        return TileType::HOLE;
    }

    // Default to floor if no cases above match
    return TileType::FLOOR;
}

// Returns the matching tle edge type for the given character. Defaults to OPEN.
TileEdgeType get_tile_edge_type_by_character(const char& character)
{  
    if (character == 'D')
    {
        return TileEdgeType::DOOR;
    }
    if (character == 'W')
    {
        return TileEdgeType::WALL;
    }

    // Default to open if no cases above match
    return TileEdgeType::OPEN;
}

// CONSTRUCTORS ---

// Constructs the level manager by reading from the given filepath.
LevelManager::LevelManager(const std::string& filepath)
{
    read_from_config_file(filepath);
}

// PUBLIC FUNCTIONS ---

// Prints all the levels and the tiles that are contained within.
void LevelManager::print_all_levels() const
{
    for (Level level: all_levels)
    {
        std::cout << "NAME: " << level.name << "\n";
        std::cout << "START X: " << level.start_position_x << "\n";
        std::cout << "START Y: " << level.start_position_y << "\n";

        for (int i = 0; i < level.tile_grid.size(); i++)
        {
            std::cout << "TILES IN ROW " << i << "\n"; 
            for (int j = 0; j < level.tile_grid[i].size(); j++)
            {
                level.tile_grid[i][j].print();
            }
        }
    }
}

// PRIVATE FUNCTIONS ---

// Reads from the given config file and attempts to setup the level details.
void LevelManager::read_from_config_file(const std::string& filepath)
{
    std::ifstream config_file_reader{ filepath, std::ifstream::in };
    if (config_file_reader)
    {
        std::cout << "Reading from level config..." << "\n";

        // Initialize stuff for reading
        int current_text_index = 0;
        int number_of_columns_per_row = 0;
        std::string current_text{};
        Level current_level{};
        std::vector<Tile> current_tile_row{};

        while (config_file_reader >> current_text)
        {
            // Handle the divider each level
            if (current_text == "~")
            {
                // Reset where we are for reading level details
                current_text_index = 0;

                // Add the current level to the level manager
                all_levels.emplace_back(current_level);

                // Reset the current level in preparation for the next
                current_level = Level{};

                // Skip the below code and start the while loop again on the next iteration
                continue;
            }

            // Handle pulling out data from the file based on where we are
            switch (current_text_index)
            {
                case 0:
                current_level.name = current_text;
                break;

                case 1:
                current_level.start_position_x = std::stoi(current_text);
                break;

                case 2:
                current_level.start_position_y = std::stoi(current_text);
                break;

                case 3:
                number_of_columns_per_row = std::stoi(current_text);
                break;

                default:
                Tile current_tile{};

                // Handle the tile type first
                TileType tileType = get_tile_type_by_abbreviation(current_text);
                current_tile.set_tile_type(tileType);

                // Handle tile edge characters...

                // Handle TOP edge
                config_file_reader >> current_text;
                TileEdgeType top_edge_type = get_tile_edge_type_by_character(current_text[0]);
                current_tile.set_edge_type_for_edge(TileEdge::TOP, top_edge_type);

                // Handle RIGHT edge
                config_file_reader >> current_text;
                TileEdgeType right_edge_type = get_tile_edge_type_by_character(current_text[0]);
                current_tile.set_edge_type_for_edge(TileEdge::RIGHT, right_edge_type);

                // Handle BOTTOM edge
                config_file_reader >> current_text;
                TileEdgeType bottom_edge_type = get_tile_edge_type_by_character(current_text[0]);
                current_tile.set_edge_type_for_edge(TileEdge::BOTTOM, bottom_edge_type);

                // Handle LEFT edge
                config_file_reader >> current_text;
                TileEdgeType left_edge_type = get_tile_edge_type_by_character(current_text[0]);
                current_tile.set_edge_type_for_edge(TileEdge::LEFT, left_edge_type);

                if (tileType == TileType::FLOOR_WITH_OBJECT)
                {
                    // Handle reading object ID
                    config_file_reader >> current_text;
                    current_tile.set_object_id(current_text);
                }

                // Add tile to the row
                current_tile_row.emplace_back(current_tile);

                // Check if the tile is the last of the row
                if (current_tile_row.size() == number_of_columns_per_row)
                {
                    // Add this row to the level grid
                    current_level.tile_grid.emplace_back(current_tile_row);

                    // Reset the row
                    current_tile_row.clear();
                }
                
                break;

            }

            // Increment the text index to keep track of where in the level we are
            current_text_index++;
        }

        std::cout << "Finished reading level config!\n";
    }
}