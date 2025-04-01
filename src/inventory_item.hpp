#pragma once
#include <string>

enum class ItemType
{
    KEY,
    NOTE,
    OBJECT,
};

struct InventoryItem
{
    std::string name;
    ItemType type;
};