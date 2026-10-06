#pragma once

// 1. Forward declaration ต้องอยู่ข้างใน namespace renderer
namespace renderer {
    class Renderer;
}

namespace script {
    void test(renderer::Renderer& renderer); // ระบุ renderer::Renderer
}