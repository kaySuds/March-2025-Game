#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "grid.hpp"
#include "grid_color_manager.hpp"
#include "level_manager.hpp"
#include "player.hpp"
#include "inventory_manager.hpp"
#include <iostream>

int main()
{
    // CREATE AND SETUP THE SFML WINDOW
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(60);

    // CREATE INVENTORY OBJECTS
    InventoryManager inventoryManager{ "res/objects_config.txt" };
    inventoryManager.print_all_items();

    LevelManager level_manager{ "res/level_config.txt" };
    level_manager.print_all_levels();

    int tile_size_pixels = 64;
     
    GridColorManager colorManager{ GridTheme::DARK };

    Player rando{ 0, 0 };

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) 
            {
                
                Tile current_tile = level_manager.get_current_player_level().tile_grid[rando.pos_y][rando.pos_x];
                TileEdgeType right_edge = current_tile.get_edge_type(TileEdge::RIGHT);
                if (right_edge == TileEdgeType::OPEN)
                {
                    rando.pos_x++;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) 
            {
                Tile current_tile = level_manager.get_current_player_level().tile_grid[rando.pos_y][rando.pos_x];
                TileEdgeType right_edge = current_tile.get_edge_type(TileEdge::LEFT);
                if (right_edge == TileEdgeType::OPEN)
                {
                    rando.pos_x--;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) 
            {
                Tile current_tile = level_manager.get_current_player_level().tile_grid[rando.pos_y][rando.pos_x];
                TileEdgeType right_edge = current_tile.get_edge_type(TileEdge::TOP);
                if (right_edge == TileEdgeType::OPEN)
                {
                    rando.pos_y--;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down)) 
            {
                Tile current_tile = level_manager.get_current_player_level().tile_grid[rando.pos_y][rando.pos_x];
                TileEdgeType right_edge = current_tile.get_edge_type(TileEdge::BOTTOM);
                if (right_edge == TileEdgeType::OPEN)
                {
                    rando.pos_y++;
                }
            }
        }

        window.clear();

        // Draw the grid
        std::vector<std::vector<Tile>> game_grid = level_manager.get_current_player_level().tile_grid;
        for (int row_index = 0; row_index < game_grid.size(); row_index++)
        {
            for(int column_index = 0; column_index < game_grid[row_index].size(); column_index++)
            {
                Tile& gridTile = game_grid[row_index][column_index];

                
                // if ((column_index == rando.pos_x) && (row_index == rando.pos_y))
                // {
                //     gridTile.reveal();   
                // }

                int y_position_pixels = row_index * tile_size_pixels;
                int x_position_pixels = column_index * tile_size_pixels;

                // Create the tile rectangle at the grid position
                sf::RectangleShape tile{ {static_cast<float>(tile_size_pixels), static_cast<float>(tile_size_pixels)} };
                tile.setPosition({ static_cast<float>(x_position_pixels), static_cast<float>(y_position_pixels)});

                // Create the top edge rectangle
                sf::RectangleShape top_tile_edge{ {static_cast<float>(tile_size_pixels), 5.f }};
                top_tile_edge.setPosition({ static_cast<float>(x_position_pixels), static_cast<float>(y_position_pixels)});

                // Create the right edge rectangle
                sf::RectangleShape right_tile_edge{ {5.f, static_cast<float>(tile_size_pixels) }};
                right_tile_edge.setPosition({ static_cast<float>(x_position_pixels) + static_cast<float>(tile_size_pixels) - 5.f, static_cast<float>(y_position_pixels)});

                // Create the bottom edge rectangle
                sf::RectangleShape bottom_tile_edge{ {static_cast<float>(tile_size_pixels), 5.f }};
                bottom_tile_edge.setPosition({ static_cast<float>(x_position_pixels), static_cast<float>(y_position_pixels) + static_cast<float>(tile_size_pixels) - 5.f} );

                // Create the left edge rectangle
                sf::RectangleShape left_tile_edge{ {5.f, static_cast<float>(tile_size_pixels) }};
                left_tile_edge.setPosition({ static_cast<float>(x_position_pixels), static_cast<float>(y_position_pixels)});

                // Apply color theme for tile and edges
                if (gridTile.get_is_revealed()) 
                {
                    tile.setFillColor(colorManager.get_revealed_tile_color_for_type(gridTile.get_tile_type()));
                    top_tile_edge.setFillColor(colorManager.get_revealed_edge_color_for_type(gridTile.get_edge_type(TileEdge::TOP)));
                    right_tile_edge.setFillColor(colorManager.get_revealed_edge_color_for_type(gridTile.get_edge_type(TileEdge::RIGHT)));
                    bottom_tile_edge.setFillColor(colorManager.get_revealed_edge_color_for_type(gridTile.get_edge_type(TileEdge::BOTTOM)));
                    left_tile_edge.setFillColor(colorManager.get_revealed_edge_color_for_type(gridTile.get_edge_type(TileEdge::LEFT)));
                } else {
                    sf::Color tile_color = colorManager.get_un_revealed_tile_color();
                    sf::Color edge_color = colorManager.get_un_revealed_tile_edge_color();

                    tile.setFillColor(tile_color);
                    top_tile_edge.setFillColor(edge_color);
                    right_tile_edge.setFillColor(edge_color);
                    bottom_tile_edge.setFillColor(edge_color);
                    left_tile_edge.setFillColor(edge_color);
                }

                // Draw the tile rect and all the edges
                window.draw(tile);
                window.draw(top_tile_edge);
                window.draw(right_tile_edge);
                window.draw(bottom_tile_edge);
                window.draw(left_tile_edge);
            }
        }

        // draw the player
        // step 1: create circle shape that's smaller than tile size (if 40 pixels, radius = 20)
        sf::CircleShape player_shape { 20.0f };
        // step 2: position circle in center of tile player is on
        //if player is at (1,1) 1 * tile size & 1 * tile size (both directions), take player's pos * tile size
        int pos_x = rando.pos_x * tile_size_pixels;
        int pos_y = rando.pos_y * tile_size_pixels;

        int centered_pos_x = pos_x + ((tile_size_pixels / 2) - 20); // offsetting x & y to get player circle centered, 20 is r
        int centered_pos_y = pos_y + ((tile_size_pixels / 2) - 20);

        player_shape.setPosition({ static_cast<float>(centered_pos_x), static_cast<float>(centered_pos_y) });

        // step 3: color it red for now
        player_shape.setFillColor(sf::Color::Red);

        window.draw(player_shape);

        window.display();
    }
}