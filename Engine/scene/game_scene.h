#pragma once
#include "scene.h"

class GameScene : public Scene
{
public:
    void Init() override;
    void Update(float delta_time) override;
    void Render() override;
    void Destroy() override;
};