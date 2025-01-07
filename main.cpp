#include <iostream>
#include <curses.h>
#include <memory>
#include <random>
#include <chrono>
#include <thread>
#include <array>
#include "utils/vec2.h"
#include "utils/rect2.h"
#include "AppState.h"
#include "FrameBuffer.h"

int main() {
    // Initialize Curses
    auto cstate = AppState::init_app();

    while (!cstate->must_close()) {
        cstate->handle_input();
        cstate->update();
        cstate->render();
        
        // sleep for 16ms
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}
