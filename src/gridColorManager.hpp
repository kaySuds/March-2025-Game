#pragma once

#include <SFML/Graphics.hpp>
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
        // Floor            Hole              Ladder            Floor + Obj
        { gray,             teal,             beige,            goldenrod },
        { sf::Color::Blue, sf::Color::Black, sf::Color::Red, sf::Color::Magenta }
    }};

    // Index by GridTheme ordinal, then index by TileEdgeType to get the color
    const std::array<std::array<sf::Color, 3>, 2> revealed_tile_edge_color_sets {{
        // Door            Wall              Open            
        { red_violet_brown, black,            mid_gray },
        { sf::Color::Yellow, sf::Color::White, sf::Color::Blue }
    }};

    const std::array<sf::Color, 2> un_revealed_tile_color_set {
        // Light           Dark
        { off_black, sf::Color::Black }
    };

    const std::array<sf::Color, 2> un_revealed_edge_color_set {
        // Light           Dark
        { black,   sf::Color::Black }
    };

    static inline constexpr sf::Color white{ 255, 255, 255 };
    static inline constexpr sf::Color black{ 0, 0, 0 };
    static inline constexpr sf::Color off_black{ 15, 15, 15 };
    static inline constexpr sf::Color mid_gray{ 200, 180, 190 };
    static inline constexpr sf::Color gray{ 242, 239, 231 };
    static inline constexpr sf::Color light_teal{ 154, 203, 208 };
    static inline constexpr sf::Color teal{ 72, 166, 167 };
    static inline constexpr sf::Color dark_teal{ 0, 106, 113 };
    static inline constexpr sf::Color beige{ 245, 238, 220 };
    static inline constexpr sf::Color goldenrod{ 221, 168, 83 };
    static inline constexpr sf::Color red_violet_brown{ 96, 70, 82 };
};