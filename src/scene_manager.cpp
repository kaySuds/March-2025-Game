//
// Created by David on 4/25/26.
//

#include "scene_manager.hpp"

GameSceneType SceneManager::get_scene() const
{
    return game_scene;
}

void SceneManager::update_scene(const GameSceneType scene)
{
    game_scene = scene;
}
