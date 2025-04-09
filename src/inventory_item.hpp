#pragma once

#include <string>

struct InventoryItem
{
    std::string name;
    std::string id;
    std::string description;

    void print() const;
};