#pragma once
#include "scene.h"
#include <memory>

namespace SceneManager
{
    void ChangeScene(std::unique_ptr<Scene> new_scene);
    void Update(float delta_time);
    void Render();
    void Destroy();
}