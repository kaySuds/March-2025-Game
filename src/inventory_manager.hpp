#pragma once

#include "inventory_item.hpp"
#include <vector>

struct InventoryManager
{
    // CONSTRUCTORS ---
    explicit InventoryManager(const std::string& filepath);

    // PUBLIC PROPERTIES ---
    std::vector<InventoryItem> all_items; // TODO: Maybe make this a map? Could then index by id

    // PUBLIC FUNCTIONS ---
    void print_all_items() const;

    void add_item_to_player_inventory(const InventoryItem& item);
    bool does_item_exist_in_player_inventory(const std::string& item_id) const;
    std::vector<InventoryItem> get_all_items_in_player_inventory();

    private:
    // PRIVATE PROPERTIES ---
    std::vector<InventoryItem> player_items;

    // PRIVATE FUNCTIONS ---
    void read_from_config(const std::string& filepath);
};