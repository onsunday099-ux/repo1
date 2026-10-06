#include "script.h"
#include "renderer/renderer.h"
#include "audio/audio.h"

namespace script {

    void testScene(renderer::Renderer& renderer, audio::Audio& audio) {
        audio.Play("assets/sound/song1.flac"); // ✅ เรียกผ่าน audio object
        renderer.LoadTexture("Test/bg/bg2.jpg");
    }

    void test(renderer::Renderer& renderer, audio::Audio& audio) {
        testScene(renderer, audio);
    }
}