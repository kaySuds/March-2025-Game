#pragma once

#include "tile.hpp"
#include "grid.hpp"
#include "level.hpp"
#include <vector>

struct LevelManager 
{
    // CONSTRUCTORS ---

    // Constructs an instance by reading from the given filepath. File must follow format outlined level_config_readme.txt!
    LevelManager(const std::string& filepath);

    // PUBLIC FUNCTIONS ---

    // Prints all the levels managed by this instance.
    void print_all_levels() const;
    // Gets the current level based on the level index.
    const Level& get_current_player_level() const;

    private:

    // PRIVATE FUNCTIONS ---

    // Called when constructing the LevelManager with a filepath.
    void read_from_config_file(const std::string& filepath);

    // PRIVATE PROPERTIES ---

    // Used to keep track of all level data.
    std::vector<Level> all_levels;
    // Used to keep track of the level occupied by the player.
    int player_level_index = 0;
};