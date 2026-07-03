#pragma once


struct InputState {
    struct Mouse {
        f32 x = 0;
        f32 y = 0;
        bool lDown = false;
        bool rDown = false;
    };

    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool quit = false;

    Mouse mouse;
};