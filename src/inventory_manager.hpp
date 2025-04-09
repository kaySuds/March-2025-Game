#pragma once

#include "inventory_item.hpp"
#include <vector>

struct InventoryManager
{
    // CONSTRUCTORS ---
    InventoryManager(const std::string& filepath);

    // PUBLIC PROPERTIES ---
    std::vector<InventoryItem> all_items;

    // PUBLIC FUNCTIONS ---
    void print_all_items() const;

    private:
    // PRIVATE FUNCTIONS ---
    void read_from_config(const std::string& filepath);
};