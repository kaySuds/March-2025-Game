#pragma once

#include "inventory_item.hpp"
#include <vector>

struct InventoryManager
{

    InventoryManager(const std::string& filepath);

    std::vector<InventoryItem> all_items;

    private:
    void read_from_config(const std::string& filepath);
};