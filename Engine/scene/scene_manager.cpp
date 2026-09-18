#include "scene_manager.h"

namespace SceneManager
{
    static std::unique_ptr<Scene> current_scene = nullptr;

    void ChangeScene(std::unique_ptr<Scene> new_scene)
    {
        if (current_scene)
        {
            current_scene->Destroy();
        }

        current_scene = std::move(new_scene);

        if (current_scene)
        {
            current_scene->Init();
        }
    }

    void Update(float delta_time)
    {
        if (current_scene)
        {
            current_scene->Update(delta_time);
        }
    }

    void Render()
    {
        if (current_scene)
        {
            current_scene->Render();
        }
    }

    void Destroy()
    {
        if (current_scene)
        {
            current_scene->Destroy();
            current_scene.reset();
        }
    }
}