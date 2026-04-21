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
    // GAME SETUP ----------

    // Create and set up inventory and all objects (Based on config file)
    // TODO: Make sure this throws or something on failure with better reporting
    InventoryManager inventoryManager{ "res/objects_config.txt" };
    inventoryManager.print_all_items();

    // Create and set up all levels (Based on config file)
    // TODO: Make sure this throws or something on failure with better reporting
    LevelManager level_manager{ "res/level_config.txt" };
    level_manager.print_all_levels();

    GridColorManager colorManager{ GridTheme::DARK };

    std::vector<std::vector<Tile>> current_level_tiles = level_manager.get_current_player_level().tile_grid;

    Player player{ 0, 0 };

    // WINDOW SETUP ----------

    // Create and set up the SFML Window
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(60);

    // TODO: Setup font
    std::string font_path = "res/ShareTech-Regular.ttf";
    sf::Font font;
    if (!font.openFromFile(font_path))
    {
        std::cerr << "WINDOW SETUP ERROR - Could not find font: " << font_path << std::endl;
        exit(EXIT_FAILURE);
    }

    // MAIN LOOP ----------

    // TODO: Add a way of managing scenes
    // 1. Add an enum of the scenes we can show in the game (game, main menu, inventory, etc.)
    // 2. Have a scene manager that manages the scene and allows us to change it

    // TODO: Add a prompt label for actions:
    // 1. Show a label in the bottom right when an action can be taken
    // 2. Poll event

    while (window.isOpen())
    {
        int tile_size_pixels = 64;

        // HANDLE EVENTS
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) 
            {
                
                Tile current_tile = level_manager.get_current_player_level().tile_grid[player.pos_y][player.pos_x];
                TileEdgeType right_edge = current_tile.get_edge_type(TileEdge::RIGHT);
                if (right_edge == TileEdgeType::OPEN)
                {
                    player.pos_x++;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) 
            {
                Tile current_tile = level_manager.get_current_player_level().tile_grid[player.pos_y][player.pos_x];
                TileEdgeType right_edge = current_tile.get_edge_type(TileEdge::LEFT);
                if (right_edge == TileEdgeType::OPEN)
                {
                    player.pos_x--;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) 
            {
                Tile current_tile = level_manager.get_current_player_level().tile_grid[player.pos_y][player.pos_x];
                TileEdgeType right_edge = current_tile.get_edge_type(TileEdge::TOP);
                if (right_edge == TileEdgeType::OPEN)
                {
                    player.pos_y--;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down)) 
            {
                Tile current_tile = level_manager.get_current_player_level().tile_grid[player.pos_y][player.pos_x];
                TileEdgeType right_edge = current_tile.get_edge_type(TileEdge::BOTTOM);
                if (right_edge == TileEdgeType::OPEN)
                {
                    player.pos_y++;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E))
            {
                std::cout << "E pressed" << std::endl;
                // We need to know where we are here
                Tile& player_tile = current_level_tiles[player.pos_y][player.pos_x];
                std::string object_id = player_tile.get_object_id();
                if (!object_id.empty())
                {
                    // TODO: Move this out to the manager later
                    for (auto& item : inventoryManager.all_items)
                    {
                        if (item.id == object_id)
                        {
                            inventoryManager.add_item_to_player_inventory(item);
                            player_tile.set_tile_type(TileType::FLOOR);
                            player_tile.set_object_id({});
                            break;
                        }
                    }
                }
            }
        }

        // DRAW TO THE SCREEN
        window.clear();

        // Draw the grid
        for (int row_index = 0; row_index < current_level_tiles.size(); row_index++)
        {
            for(int column_index = 0; column_index < current_level_tiles[row_index].size(); column_index++)
            {
                Tile& gridTile = current_level_tiles[row_index][column_index];

                
                if ((column_index == player.pos_x) && (row_index == player.pos_y))
                {
                    gridTile.reveal();

                    if (!gridTile.get_object_id().empty())
                    {
                        // Draw pickup label
                        sf::Text pickup_text(font, "Press E to pick up", 12);
                        pickup_text.setPosition({0.0, 0.0});
                        window.draw(pickup_text);
                    }
                }

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

        // Draw the player
        // step 1: create circle shape that's smaller than tile size (if 40 pixels, radius = 20)
        sf::CircleShape player_shape { 20.0f };
        // step 2: position circle in center of tile player is on
        //if player is at (1,1) 1 * tile size & 1 * tile size (both directions), take player's pos * tile size
        int pos_x = player.pos_x * tile_size_pixels;
        int pos_y = player.pos_y * tile_size_pixels;

        int centered_pos_x = pos_x + ((tile_size_pixels / 2) - 20); // offsetting x & y to get player circle centered, 20 is r
        int centered_pos_y = pos_y + ((tile_size_pixels / 2) - 20);

        player_shape.setPosition({ static_cast<float>(centered_pos_x), static_cast<float>(centered_pos_y) });

        // step 3: color it red for now
        player_shape.setFillColor(sf::Color::Red);

        window.draw(player_shape);

        // Display the drawing
        window.display();
    }
}