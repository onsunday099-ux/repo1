#include "script.h"
#include "renderer/renderer.h" // ต้อง include ไฟล์นี้เพื่อให้รู้จักคลาสเต็ม
#include "audio/audio.h"

namespace script {
    

    void testSence{
        audio::Audio::Play("assets/sound/song1.flac")
        renderer.LoadTexture("Test/bg/bg2.jpg");
        
    }

    void test(renderer::Renderer& renderer) {
        testSence();
    }
}