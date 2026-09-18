#pragma once

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void Init() = 0;
    virtual void Update(float delta_time) = 0;
    virtual void Render() = 0;
    virtual void Destroy() = 0;
};