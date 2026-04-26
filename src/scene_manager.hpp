//
// Created by David on 4/25/26.
//

#ifndef MYPROJECT_SCENE_MANAGER_HPP
#define MYPROJECT_SCENE_MANAGER_HPP

#endif //MYPROJECT_SCENE_MANAGER_HPP

// Enumerates the types of scenes in the game.
enum class GameSceneType
{
    GAMEPLAY,
    INVENTORY_MENU,
};

// Manages the currently displayed scene.
struct SceneManager
{
    void update_scene(GameSceneType scene);
    [[nodiscard]] GameSceneType get_scene() const;
private:
    GameSceneType game_scene = GameSceneType::GAMEPLAY;
};