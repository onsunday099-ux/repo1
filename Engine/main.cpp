#include "Engine.h"
#include "core/Logger.h"

int main(int argc, char* argv[])
{
    Logger::Init();

    if (Engine::Init())
    {
        Engine::Run();
    }

    Engine::Destroy();

    return 0;
}