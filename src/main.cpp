#include <SFML/Graphics.hpp>
#include "grid.hpp"

int main()
{
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(60);

    int tile_size_pixels = 64;
    Grid gameGrid{ 5, 5 };
    gameGrid.print();

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
                int y_position_pixels = row_index * tile_size_pixels;
                int x_position_pixels = column_index * tile_size_pixels;

                sf::RectangleShape tile{ {static_cast<float>(tile_size_pixels), static_cast<float>(tile_size_pixels)} };
                tile.setPosition({ static_cast<float>(x_position_pixels), static_cast<float>(y_position_pixels)});
                tile.setFillColor(sf::Color::Red);

                sf::RectangleShape top_tile_edge{ {static_cast<float>(tile_size_pixels), 5.f }};
                top_tile_edge.setPosition({ static_cast<float>(x_position_pixels), static_cast<float>(y_position_pixels)});
                top_tile_edge.setFillColor(sf::Color::Blue);

                sf::RectangleShape right_tile_edge{ {5.f, static_cast<float>(tile_size_pixels) }};
                right_tile_edge.setPosition({ static_cast<float>(x_position_pixels) + static_cast<float>(tile_size_pixels) - 5.f, static_cast<float>(y_position_pixels)});
                right_tile_edge.setFillColor(sf::Color::Green);

                sf::RectangleShape bottom_tile_edge{ {static_cast<float>(tile_size_pixels), 5.f }};
                bottom_tile_edge.setPosition({ static_cast<float>(x_position_pixels), static_cast<float>(y_position_pixels) + static_cast<float>(tile_size_pixels) - 5.f} );
                bottom_tile_edge.setFillColor(sf::Color::Yellow);

                sf::RectangleShape left_tile_edge{ {5.f, static_cast<float>(tile_size_pixels) }};
                left_tile_edge.setPosition({ static_cast<float>(x_position_pixels), static_cast<float>(y_position_pixels)});
                left_tile_edge.setFillColor(sf::Color::Magenta);


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