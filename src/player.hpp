#pragma once
#include "inventory_item.hpp"
#include <vector>

struct Player 
{
    // player constructor: takes in int x & int y, initialize by giving pos x & pos y & health default values
    Player(): pos_x(0), pos_y(0), health(100) {}
    Player(int x, int y): pos_x(x), pos_y(y), health(100) {}
    Player(int h): pos_x(0), pos_y(0), health(h) {}
    Player(std::vector<InventoryItem> inv): pos_x(0), pos_y(0), health(100), inventory(inv) {}

    // player position
    int pos_x;
    int pos_y;

    // HP
    int health;

    // for later: list of status effects/things that can injure player

    // list of items player can have (keys, etc.)
    std::vector<InventoryItem> inventory;
};