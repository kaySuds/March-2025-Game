#pragma once

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
    Tile(TileType t, bool revealed): type(t), isRevealed(revealed)
    {
        edges[static_cast<int>(TileEdge::TOP)] = TileEdgeType::OPEN;
        edges[static_cast<int>(TileEdge::RIGHT)] = TileEdgeType::OPEN;
        edges[static_cast<int>(TileEdge::BOTTOM)] = TileEdgeType::OPEN;
        edges[static_cast<int>(TileEdge::LEFT)] = TileEdgeType::OPEN;
    }

    TileEdgeType getEdgeType(TileEdge edge) const;
    void print() const;

    void setEdgeTypeForEdge(TileEdge edge, TileEdgeType edgeType);

    private:

    TileType type;
    bool isRevealed;
    TileEdgeType edges[4]; 
};