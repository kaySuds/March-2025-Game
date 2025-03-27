#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "gridColorManager.hpp"

int main()
{
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(60);

    int tile_size_pixels = 64;
    Grid gameGrid{ 5, 5 };
    gameGrid.print();
     
    GridColorManager colorManager{ GridTheme::LIGHT };

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();

        // Draw the grid
        for (int row_index = 0; row_index < gameGrid.get_row_count(); row_index++)
        {
            for(int column_index = 0; column_index < gameGrid.get_column_count(); column_index++)
            {
                Tile gridTile = gameGrid.get_tile_at_position(column_index, row_index);

                int y_position_pixels = row_index * tile_size_pixels;
                int x_position_pixels = column_index * tile_size_pixels;

                sf::RectangleShape tile{ {static_cast<float>(tile_size_pixels), static_cast<float>(tile_size_pixels)} };
                tile.setPosition({ static_cast<float>(x_position_pixels), static_cast<float>(y_position_pixels)});

                sf::RectangleShape top_tile_edge{ {static_cast<float>(tile_size_pixels), 5.f }};
                top_tile_edge.setPosition({ static_cast<float>(x_position_pixels), static_cast<float>(y_position_pixels)});

                sf::RectangleShape right_tile_edge{ {5.f, static_cast<float>(tile_size_pixels) }};
                right_tile_edge.setPosition({ static_cast<float>(x_position_pixels) + static_cast<float>(tile_size_pixels) - 5.f, static_cast<float>(y_position_pixels)});

                sf::RectangleShape bottom_tile_edge{ {static_cast<float>(tile_size_pixels), 5.f }};
                bottom_tile_edge.setPosition({ static_cast<float>(x_position_pixels), static_cast<float>(y_position_pixels) + static_cast<float>(tile_size_pixels) - 5.f} );

                sf::RectangleShape left_tile_edge{ {5.f, static_cast<float>(tile_size_pixels) }};
                left_tile_edge.setPosition({ static_cast<float>(x_position_pixels), static_cast<float>(y_position_pixels)});

                // Apply color theme for tile
                if (gridTile.get_is_revealed()) 
                {
                    tile.setFillColor(colorManager.get_revealed_tile_color_for_type(gridTile.get_tile_type()));
                    top_tile_edge.setFillColor(colorManager.get_revealed_edge_color_for_type(gridTile.get_edge_type(TileEdge::TOP)));
                    right_tile_edge.setFillColor(colorManager.get_revealed_edge_color_for_type(gridTile.get_edge_type(TileEdge::RIGHT)));
                    bottom_tile_edge.setFillColor(colorManager.get_revealed_edge_color_for_type(gridTile.get_edge_type(TileEdge::BOTTOM)));
                    left_tile_edge.setFillColor(colorManager.get_revealed_edge_color_for_type(gridTile.get_edge_type(TileEdge::LEFT)));
                } else {
                    sf::Color un_revealed_color = colorManager.get_un_revealed_tile_color();

                    tile.setFillColor(un_revealed_color);
                    top_tile_edge.setFillColor(un_revealed_color);
                    right_tile_edge.setFillColor(un_revealed_color);
                    bottom_tile_edge.setFillColor(un_revealed_color);
                    left_tile_edge.setFillColor(un_revealed_color);
                }

                window.draw(tile);
                window.draw(top_tile_edge);
                window.draw(right_tile_edge);
                window.draw(bottom_tile_edge);
                window.draw(left_tile_edge);
            }
        }

        window.display();
    }
}