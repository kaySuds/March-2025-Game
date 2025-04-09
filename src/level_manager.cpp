#include "level_manager.hpp"
#include <fstream>
#include <iostream>

// CONSTRUCTORS ---
LevelManager::LevelManager(const std::string& filepath)
{
    read_from_config_file(filepath);
}

// PUBLIC FUNCTIONS ---
void LevelManager::print_all_levels() const
{
    std::cout << "TODO!\n";
}

// PRIVATE FUNCTIONS ---
void LevelManager::read_from_config_file(const std::string& filepath)
{
    std::ifstream config_file_reader{ filepath, std::ifstream::in };
    if (config_file_reader)
    {
        int current_line_index = 0;
        int current_count = 0;

        // TODO: Something like this rather than std::getline
        // config_file_reader >> current_line; // Sub-Basement
        // config_file_reader >> current_line; // 0
        // config_file_reader >> current_line; // 0

        std::string current_line;
        while (std::getline(config_file_reader, current_line))
        {
            std::cout << current_line << "\n";
        }
    }
}