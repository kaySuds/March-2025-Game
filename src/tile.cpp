#include <iostream>
#include "tile.hpp"

// Switch that will get the string name of the tile type from above enum.
std::string get_tile_type_name(TileType type)
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
std::string get_tile_edge_name(TileEdge edge)
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
std::string get_tile_edge_type_name(TileEdgeType type)
{
    switch (type)
    {
    case TileEdgeType::DOOR: return "DOOR";
    case TileEdgeType::OPEN: return "OPEN";
    case TileEdgeType::WALL: return "WALL";
    }
}

TileEdgeType Tile::get_edge_type(TileEdge edge) const
{
    return edges[static_cast<int>(edge)];
}

void Tile::set_edge_type_for_edge(TileEdge edge, TileEdgeType edge_type)
{

    edges[static_cast<int>(edge)] = edge_type;
}

void Tile::print() const
{
    std::cout << "Tile is a " << get_tile_type_name(type) << ", " << get_tile_edge_name(TileEdge::TOP) << ": " << get_tile_edge_type_name(get_edge_type(TileEdge::TOP)) << ", " << get_tile_edge_name(TileEdge::RIGHT) << ": " << get_tile_edge_type_name(get_edge_type(TileEdge::RIGHT)) << ", " << get_tile_edge_name(TileEdge::BOTTOM) << ": " << get_tile_edge_type_name(get_edge_type(TileEdge::BOTTOM)) << ", " << get_tile_edge_name(TileEdge::LEFT) << ": " << get_tile_edge_type_name(get_edge_type(TileEdge::LEFT)) << '\n';
}

bool Tile::get_is_revealed() const 
{
    return is_revealed;
}

void Tile::reveal() 
{
    is_revealed = true;
}


TileType Tile::get_tile_type() const
{
    return type;
}

void Tile::set_tile_type(TileType new_type)
{
    type = new_type;
}

std::string Tile::get_object_id() const
{
    return object_id;
}

void Tile::set_object_id(const std::string& new_id)
{
    object_id = new_id;
}