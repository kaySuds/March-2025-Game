#pragma once
#include <string>

// Represents the type the makes up the main (center) part of a tile.
enum class TileType
{
    FLOOR,
    HOLE,
    LADDER,
    FLOOR_WITH_OBJECT
};

// Enumerates the edges a particular tile can have.
enum class TileEdge
{
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};

// Represents the type that makes up edges or a tile.
enum class TileEdgeType
{
    DOOR,
    WALL,
    OPEN
};

// Represents a single grid tile in our game.
struct Tile
{
    Tile(TileType t, bool revealed): type(t), is_revealed(revealed)
    {
        edges[static_cast<int>(TileEdge::TOP)] = TileEdgeType::OPEN;
        edges[static_cast<int>(TileEdge::RIGHT)] = TileEdgeType::OPEN;
        edges[static_cast<int>(TileEdge::BOTTOM)] = TileEdgeType::OPEN;
        edges[static_cast<int>(TileEdge::LEFT)] = TileEdgeType::OPEN;
    }

    TileEdgeType get_edge_type(TileEdge edge) const;
    void set_edge_type_for_edge(TileEdge edge, TileEdgeType edge_type);

    bool get_is_revealed() const;
    void reveal();

    TileType get_tile_type() const;
    void set_tile_type(TileType new_type);

    void print() const;

    private:

    TileType type;
    bool is_revealed;
    TileEdgeType edges[4]; 
};