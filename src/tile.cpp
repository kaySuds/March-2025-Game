#include <iostream>
#include "tile.hpp"

TileEdgeType Tile::getEdgeType(TileEdge edge) const
{
    return edges[static_cast<int>(edge)];
}

void Tile::setEdgeTypeForEdge(TileEdge edge, TileEdgeType edgeType)
{
    edges[static_cast<int>(edge)] = edgeType;
}

void Tile::print() const
{
    std::cout << "TILE: " << "Type: " << static_cast<int>(type) << "\n";
}