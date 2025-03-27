#pragma once

#include <SFML/Graphics/Color.hpp>
#include <array>
#include "tile.hpp"

enum class GridTheme
{
    LIGHT, DARK
};

struct GridColorManager
{
    GridColorManager(GridTheme t): theme(t) {}

    sf::Color get_revealed_tile_color_for_type(TileType tileType) const;
    sf::Color get_revealed_edge_color_for_type(TileEdgeType edgeType) const;

    sf::Color get_un_revealed_tile_color() const;
    sf::Color get_un_revealed_tile_edge_color() const;

    private:
    GridTheme theme;

    // Index by GridTheme ordinal, then index by TileType to get the color
    const std::array<std::array<sf::Color, 4>, 2> revealed_tile_color_sets {{
        // Floor            Hole              Ladder        Floor + Obj
        { light_gray,       teal,             beige,        goldenrod }, // LIGHT
        { dark_gray,        dark_teal,        gray,         goldenrod }  // DARK
    }};

    // Index by GridTheme ordinal, then index by TileEdgeType to get the color
    const std::array<std::array<sf::Color, 3>, 2> revealed_tile_edge_color_sets {{
        // Door             Wall              Open            
        { red_violet_brown, black,            gray },    // LIGHT
        { dark_brown,       black,            mid_gray } // DARK
    }};

    const std::array<sf::Color, 2> un_revealed_tile_color_set {
        // Light             Dark
        { off_black,         off_black }
    };

    const std::array<sf::Color, 2> un_revealed_edge_color_set {
        // Light             Dark
        { black,             black }
    };
    
    static inline constexpr sf::Color white{ 255, 255, 255 };
    static inline constexpr sf::Color black{ 0, 0, 0 };
    static inline constexpr sf::Color off_black{ 15, 15, 15 };
    static inline constexpr sf::Color dark_gray{ 75, 75, 75 };
    static inline constexpr sf::Color mid_gray{ 120, 120, 120 };
    static inline constexpr sf::Color gray{ 200, 180, 190 };
    static inline constexpr sf::Color light_gray{ 242, 239, 231 };
    static inline constexpr sf::Color light_teal{ 154, 203, 208 };
    static inline constexpr sf::Color teal{ 72, 166, 167 };
    static inline constexpr sf::Color dark_teal{ 0, 106, 113 };
    static inline constexpr sf::Color beige{ 245, 238, 220 };
    static inline constexpr sf::Color goldenrod{ 221, 168, 83 };
    static inline constexpr sf::Color red_violet_brown{ 96, 70, 82 };
    static inline constexpr sf::Color dark_brown{ 40, 20, 32 };
};