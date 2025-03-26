#include <iostream>
#include "tile.hpp"

// Switch that will get the string name of the tile type from above enum.
std::string getTileTypeName(TileType type)
{  
	switch (type) 
	{  
	case TileType::FLOOR:               return "FLOOR";  
	case TileType::HOLE:                return "HOLE";
	case TileType::LADDER:              return "LADDER";
	case TileType::FLOOR_WITH_OBJECT:   return "FLOOR_WITH_OBJECT";
	default:                            return "UNKNOWN";  
	}  
}

// Takes in an edge & gives us the string name.
std::string getTileEdgeName(TileEdge edge)
{
    switch (edge)
    {
    case TileEdge::TOP:     return "TOP";
    case TileEdge::RIGHT:   return "RIGHT";
    case TileEdge::BOTTOM:  return "BOTTOM";
    case TileEdge::LEFT:    return "LEFT";
    default:                return "UNKNOWN";
    }
}

// Takes in an edge type & gives us the string name.
std::string getTileEdgeTypeName(TileEdgeType type)
{
    switch (type)
    {
    case TileEdgeType::DOOR: return "DOOR";
    case TileEdgeType::OPEN: return "OPEN";
    case TileEdgeType::WALL: return "WALL";
    }
}

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
    std::cout << "Tile is a " << getTileTypeName(type) << ", " << getTileEdgeName(TileEdge::TOP) << ": " << getTileEdgeTypeName(getEdgeType(TileEdge::TOP)) << ", " << getTileEdgeName(TileEdge::RIGHT) << ": " << getTileEdgeTypeName(getEdgeType(TileEdge::RIGHT)) << ", " << getTileEdgeName(TileEdge::BOTTOM) << ": " << getTileEdgeTypeName(getEdgeType(TileEdge::BOTTOM)) << ", " << getTileEdgeName(TileEdge::LEFT) << ": " << getTileEdgeTypeName(getEdgeType(TileEdge::LEFT)) << '\n';
}