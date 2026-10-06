#pragma once

namespace renderer {
    class Renderer;
}

namespace audio {
    class Audio; // Forward declaration
}

namespace script {
    void test(renderer::Renderer& renderer, audio::Audio& audio); // เพิ่ม audio
}