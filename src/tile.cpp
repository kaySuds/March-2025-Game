#include <iostream>
#include "tile.hpp"

const TileEdgeType Tile::getEdgeType(TileEdge edge) 
{
    return edges[static_cast<int>(edge)];
}

void Tile::setEdgeTypeForEdge(TileEdge edge, TileEdgeType edgeType)
{
    edges[static_cast<int>(edge)] = edgeType;
}

const void Tile::print() 
{


    std::cout << "TILE: " << "TODO: Add more details" << "\n";
}