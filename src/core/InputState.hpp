#pragma once

struct ButtonState {
    bool current = false;
    bool previous = false;

    [[nodiscard]]
    bool pressed() const {
        return current && !previous;
    }

    [[nodiscard]]
    bool released() const {
        return !current && previous;
    }

    [[nodiscard]]
    bool down() const {
        return current;
    }
};

struct InputState {
    struct Mouse {
        f32 x = 0;
        f32 y = 0;
        ButtonState left;
        ButtonState right;
    };

    ButtonState up ;
    ButtonState down;
    ButtonState left;
    ButtonState right;

    Mouse mouse;

    void endFrame() {
        up.previous = up.current;
        down.previous = down.current;
        left.previous = left.current;
        right.previous = right.current;

        mouse.left.previous = mouse.left.current;
        mouse.right.previous = mouse.right.current;
    }
};

