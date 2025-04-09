#include "inventory_item.hpp"
#include <iostream>

void InventoryItem::print() const 
{
    std::cout << "NAME: " << name << "\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "DESCRIPTION: " << description << "\n";
}