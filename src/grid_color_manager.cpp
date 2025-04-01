#include "grid_color_manager.hpp"

sf::Color GridColorManager::get_revealed_tile_color_for_type(TileType tileType) const
{
    int theme_ordinal = static_cast<int>(theme);
    int tile_type_ordinal = static_cast<int>(tileType);

    return revealed_tile_color_sets[theme_ordinal][tile_type_ordinal];
}

sf::Color GridColorManager::get_revealed_edge_color_for_type(TileEdgeType edgeType) const
{
    int theme_ordinal = static_cast<int>(theme);
    int edge_type_ordinal = static_cast<int>(edgeType);

    return revealed_tile_edge_color_sets[theme_ordinal][edge_type_ordinal];
}

sf::Color GridColorManager::get_un_revealed_tile_color() const
{
    int theme_ordinal = static_cast<int>(theme);

    return un_revealed_tile_color_set[theme_ordinal];
}

sf::Color GridColorManager::get_un_revealed_tile_edge_color() const
{
    int theme_ordinal = static_cast<int>(theme);

    return un_revealed_edge_color_set[theme_ordinal];
}