#include "inventory_manager.hpp"
#include <fstream>
#include <iostream>

// CONSTRUCTORS ---
InventoryManager::InventoryManager(const std::string& filepath)
{
    read_from_config(filepath);
}

// PUBLIC FUNCTIONS ---
void InventoryManager::print_all_items() const
{
    std::cout << "PRINTING ALL ITEMS:\n";
    for (int i = 0; i < all_items.size(); i++) {
        // Let's get the inventory item at index i
        all_items[i].print();
    }
}

// PRIVATE FUNCTIONS ---
void InventoryManager::read_from_config(const std::string& filepath)
{
    std::ifstream config_file_reader{ filepath, std::ifstream::in };
    if (config_file_reader)
    {
        // std::cout << "Opened the config file successfully! :)\n";
        std::string current_line;

        // We will use this to setup properties
        InventoryItem current_item;

        int current_count = 0;
        char delim = '\n';
        // If count is 0 -> This line is the Name line
        // If count is 1 -> This line is the ID line
        // If count is 2 -> This line is the start line of the description
        //                  In this case, we will update the delim for getline from '\n' to '~'

        // While we can get a line from the file (not at the end)
        // Maybe update the get line funtion delim with something like '~'
        while (std::getline(config_file_reader, current_line, delim))
        {
            if (current_line.length() == 0)
            {
                // Ignore blank reads -- probably end of object
                continue;
            }
             // Should have the current line that was read from the file
            //  std::cout << "CURRENT LINE: " << current_line << "\n";
            //  std::cout << "CURRENT COUNT: " << current_count << "\n";

            if (current_count == 0)
            {
                // NAME
                current_item.name = current_line;
                current_count++;
                // std::cout << "SETTING NAME: " << current_item.name << "\n";
            }
            else if (current_count == 1)
            {
                // ID
                current_item.id = current_line;
                current_count++;
                delim = '~';
                // std::cout << "SETTING ID: " << current_item.id << "\n";
            }
            else 
            {
                // DESCRIPTION
                current_item.description = current_line;

                // std::cout << "SETTING DESCRIPTION: " << current_item.description << "\n";

                // ADD IT TO THE LIST
                // NOT SURE ABOUT COPY
                all_items.emplace_back(current_item);

                // std::cout << "ADDED THE ITEM\n";

                // RESET THE DELIM
                delim = '\n';
                // RESET THE COUNT
                current_count = 0;
            }
        }
    }
    else 
    {
        std::cout << "FAILED TO OPEN FILE!!\n";
    }
}

