#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "grid.hpp"
#include "grid_color_manager.hpp"
#include "level_manager.hpp"
#include "player.hpp"
#include "inventory_manager.hpp"
#include <iostream>

#include "scene_manager.hpp"

std::vector<std::string> split(const std::string &text, const char delim)
{
    std::vector<std::string> result{};
    std::string current_line{};
    for (const auto character: text)
    {
        if (character != delim)
        {
            current_line.push_back(character);
        }
        else
        {
            result.push_back(current_line);
            current_line = {};
        }
    }
    if (!current_line.empty())
    {
        result.push_back(current_line);
    }
    return result;
}

// Checks if the argument text will overflow onto new lines based on the max width, font, and text size.
std::vector<std::string> check_and_split_multiline(const std::string &text, const sf::Font &font, const unsigned int text_size, const unsigned int max_width)
{
    const sf::Text text_drawable{font, text, text_size};

    std::vector<std::string> result{};
    std::string current_line{};

    float current_width = 0.f;
    float last_char_width = 0.f;

    for (size_t i = 0; i < text.length(); i++)
    {
        const sf::Vector2f character_pos = text_drawable.findCharacterPos(i);
        float character_width = character_pos.x - last_char_width;

        if (current_width + character_width < static_cast<float>(max_width))
        {
            current_line.push_back(text[i]);
            current_width += character_width;
        }
        else
        {
            result.push_back(current_line);
            current_line = {text[i]};
            current_width = character_width;
        }

        last_char_width = character_pos.x;
    }

    if (!current_line.empty())
    {
        result.push_back(current_line);
    }

    return result;
}

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

    SceneManager scene_manager{};

    // std::vector<std::vector<Tile>> current_level_tiles = level_manager.get_current_player_level().tile_grid;

    Player player{ 0, 0 };

    int inventory_button_debounce_frames = 0;
    int missing_key_debounce_frames = 0;
    bool can_interact = false;

    float inventory_scroll_offset = 8.f;

    // WINDOW SETUP ----------

    // Create and set up the SFML Window
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({350u, 350u}), "CMake SFML Project");
    window.setFramerateLimit(60);

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
                TileEdgeType left_edge = current_tile.get_edge_type(TileEdge::LEFT);
                if (left_edge == TileEdgeType::OPEN)
                {
                    player.pos_x--;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) 
            {
                if (scene_manager.get_scene() == GameSceneType::GAMEPLAY)
                {
                    Tile current_tile = level_manager.get_current_player_level().tile_grid[player.pos_y][player.pos_x];
                    TileEdgeType top_edge = current_tile.get_edge_type(TileEdge::TOP);
                    if (top_edge == TileEdgeType::OPEN)
                    {
                        player.pos_y--;
                    }
                }
                else
                {
                    inventory_scroll_offset += 12.f;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down)) 
            {
                if (scene_manager.get_scene() == GameSceneType::GAMEPLAY)
                {
                    Tile current_tile = level_manager.get_current_player_level().tile_grid[player.pos_y][player.pos_x];
                    TileEdgeType down_edge = current_tile.get_edge_type(TileEdge::BOTTOM);
                    if (down_edge == TileEdgeType::OPEN)
                    {
                        player.pos_y++;
                    }
                }
                else
                {
                    inventory_scroll_offset -= 12.f;
                }
            }

            // HANDLE HOLES
            if (level_manager.get_current_player_level().tile_grid[player.pos_y][player.pos_x].get_tile_type() == TileType::HOLE)
            {
                level_manager.get_current_player_level().tile_grid[player.pos_y][player.pos_x].reveal();
                level_manager.set_player_level_index(level_manager.get_player_level_index() - 1);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E))
            {
                // We need to know where we are here
                Tile& player_tile = level_manager.get_current_player_level().tile_grid[player.pos_y][player.pos_x];
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
                if (player_tile.get_tile_type() == TileType::LADDER)
                {
                    // Transition to next level!
                    // 1. Increment the level index
                    level_manager.set_player_level_index(level_manager.get_player_level_index() + 1);
                    // 2. Set the position to the start position
                    player.pos_x = level_manager.get_current_player_level().start_position_x;
                    player.pos_y = level_manager.get_current_player_level().start_position_y;
                }
                if (can_interact)
                {
                    // TODO: REPLACE WITH REAL LOGIC
                    bool can_open_door = false;
                    switch (level_manager.get_player_level_index())
                    {
                        case 0:
                            can_open_door = inventoryManager.does_item_exist_in_player_inventory("Key-1");
                            break;
                        case 2:
                            can_open_door = inventoryManager.does_item_exist_in_player_inventory("Key-2");
                            break;
                        case 4:
                            can_open_door = inventoryManager.does_item_exist_in_player_inventory("Key-3");
                            break;
                        default:
                            can_open_door = false;
                            break;
                    }
                    if (!can_open_door)
                    {
                        missing_key_debounce_frames = 120;
                    }
                    else
                    {
                        TileEdge door_edge;
                        if (level_manager.get_current_player_level().tile_grid[player.pos_y][player.pos_x].get_edge_type(TileEdge::RIGHT) == TileEdgeType::DOOR)
                            door_edge = TileEdge::RIGHT;
                        else if (level_manager.get_current_player_level().tile_grid[player.pos_y][player.pos_x].get_edge_type(TileEdge::BOTTOM) == TileEdgeType::DOOR)
                            door_edge = TileEdge::BOTTOM;
                        else if (level_manager.get_current_player_level().tile_grid[player.pos_y][player.pos_x].get_edge_type(TileEdge::LEFT) == TileEdgeType::DOOR)
                            door_edge = TileEdge::LEFT;
                        else
                            door_edge = TileEdge::TOP;

                        level_manager.get_current_player_level().tile_grid[player.pos_y][player.pos_x].set_edge_type_for_edge(door_edge, TileEdgeType::OPEN);
                    }

                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::I))
            {
                if (inventory_button_debounce_frames <= 0)
                {
                    inventory_button_debounce_frames = 10;
                    if (scene_manager.get_scene() == GameSceneType::GAMEPLAY)
                    {
                        scene_manager.update_scene(GameSceneType::INVENTORY_MENU);
                    }
                    else
                    {
                        inventory_scroll_offset = 8.f;
                        scene_manager.update_scene(GameSceneType::GAMEPLAY);
                    }
                }
            }
        }

        if (inventory_button_debounce_frames > 0)
        {
            inventory_button_debounce_frames--;
        }
        if (missing_key_debounce_frames > 0)
        {
            missing_key_debounce_frames--;
        }

        // DRAW TO THE SCREEN
        window.clear();

        switch (scene_manager.get_scene())
        {
            case GameSceneType::GAMEPLAY:
            {
                // Draw the grid
                for (int row_index = 0; row_index < level_manager.get_current_player_level().tile_grid.size(); row_index++)
                {
                    for (int column_index = 0; column_index < level_manager.get_current_player_level().tile_grid[row_index].size(); column_index++)
                    {
                        Tile& gridTile = level_manager.get_current_player_level().tile_grid[row_index][column_index];

                        if ((column_index == player.pos_x) && (row_index == player.pos_y))
                        {
                            gridTile.reveal();

                            if (!gridTile.get_object_id().empty())
                            {
                                // Draw pickup label
                                sf::Text pickup_text(font, "Press E to pick up", 12);
                                pickup_text.setPosition({static_cast<float>(level_manager.get_current_player_level().tile_grid.size() * tile_size_pixels)  - pickup_text.getLocalBounds().size.x, static_cast<float>(level_manager.get_current_player_level().tile_grid[0].size() * tile_size_pixels)});
                                pickup_text.setFillColor({255, 255, 255, 100});
                                window.draw(pickup_text);
                            }
                            if (gridTile.has_a_door())
                            {
                                // Draw open door label
                                can_interact = true;

                                std::string pickup_description = "Press E to open";
                                if (missing_key_debounce_frames > 0)
                                {
                                    pickup_description = "Hmm... It's locked";
                                }
                                sf::Text pickup_text(font, pickup_description, 12);
                                pickup_text.setPosition({static_cast<float>(level_manager.get_current_player_level().tile_grid.size() * tile_size_pixels) - pickup_text.getLocalBounds().size.x, static_cast<float>(level_manager.get_current_player_level().tile_grid[0].size() * tile_size_pixels)});
                                pickup_text.setFillColor({255, 255, 255, 100});
                                window.draw(pickup_text);
                            }
                            if (gridTile.get_tile_type() == TileType::LADDER)
                            {
                                // Draw open door label
                                can_interact = true;

                                sf::Text pickup_text(font, "Press E to climb", 12);
                                pickup_text.setPosition({static_cast<float>(level_manager.get_current_player_level().tile_grid.size() * tile_size_pixels) - pickup_text.getLocalBounds().size.x, static_cast<float>(level_manager.get_current_player_level().tile_grid[0].size() * tile_size_pixels)});
                                pickup_text.setFillColor({255, 255, 255, 100});
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
                // Level text
                sf::Text level_text(font, level_manager.get_current_level_name(), 12);
                level_text.setFillColor({255, 255, 255, 255});
                level_text.setPosition({0, static_cast<float>(level_manager.get_current_player_level().tile_grid[0].size() * tile_size_pixels)});

                window.draw(level_text);

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
                break;
            }
            case GameSceneType::INVENTORY_MENU:
            {
                // DESIGN:
                // Inventory
                // _____________________
                // | OBJECT_NAME        |
                // | OBJECT_DESCRIPTION |
                // ----------------------

                // Text/layout constants
                constexpr float vertical_text_spacing = 8.0f;
                constexpr float horizontal_text_padding = 8.0f;
                constexpr float title_divider_width = 2.f;
                constexpr float row_divider_width = 1.f;

                constexpr unsigned int header_character_size = 28;
                constexpr unsigned int item_name_character_size = 20;
                constexpr unsigned int item_description_character_size = 16;

                // Layout variables
                float current_y_positioning = inventory_scroll_offset;

                // HEADER

                sf::Text title_text(font, "INVENTORY", header_character_size);
                title_text.setFillColor(sf::Color::White);
                title_text.setPosition({horizontal_text_padding, current_y_positioning});

                sf::RectangleShape title_background{ {title_text.getLocalBounds().size.x + 2.f * horizontal_text_padding, title_text.getLocalBounds().size.y + 2.f * vertical_text_spacing }};
                title_background.setFillColor({255, 255, 255, 75});
                title_background.setPosition({0, current_y_positioning});

                sf::RectangleShape title_divider{ {static_cast<float>(window.getSize().x), title_divider_width }};
                title_divider.setFillColor({255, 255, 255, 75});
                title_divider.setPosition({0, current_y_positioning + title_background.getSize().y});

                window.draw(title_text);
                window.draw(title_background);
                window.draw(title_divider);

                current_y_positioning = current_y_positioning + title_background.getLocalBounds().size.y + vertical_text_spacing + title_divider_width;

                for (auto &item : inventoryManager.get_all_items_in_player_inventory())
                {
                    sf::Text name_text(font, item.name, item_name_character_size);
                    name_text.setPosition({horizontal_text_padding, current_y_positioning});
                    name_text.setFillColor(sf::Color::White);

                    std::vector<std::string> description_lines = split(item.description, '\n');

                    float total_description_height = 0.f;

                    for (const auto& description_line: description_lines)
                    {
                        std::vector<std::string> description_split = check_and_split_multiline(description_line, font, item_description_character_size, window.getSize().x - static_cast<unsigned int>(horizontal_text_padding * 4.0f));

                        for (const auto & multi_line : description_split)
                        {
                            sf::Text description_text(font, multi_line, item_description_character_size);
                            description_text.setPosition({horizontal_text_padding, current_y_positioning + name_text.getLocalBounds().size.y + vertical_text_spacing + total_description_height});
                            description_text.setFillColor({255, 255, 255, 126});

                            total_description_height += description_text.getLocalBounds().size.y + vertical_text_spacing;

                            window.draw(description_text);
                        }
                    }

                    sf::RectangleShape divider{ {static_cast<float>(window.getSize().x), row_divider_width }};
                    divider.setFillColor({255, 255, 255, 75});
                    divider.setPosition({0, current_y_positioning + name_text.getLocalBounds().size.y + vertical_text_spacing + total_description_height + vertical_text_spacing});

                    window.draw(name_text);
                    window.draw(divider);

                    current_y_positioning = current_y_positioning + name_text.getLocalBounds().size.y + vertical_text_spacing + total_description_height + vertical_text_spacing + row_divider_width + vertical_text_spacing;
                }
                break;
            }
        }

        // Display the drawing
        window.display();
    }
}
