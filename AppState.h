#ifndef APPSTATE_H
#define APPSTATE_H

#include <curses.h>
#include <memory>
#include <random>
#include <array>
#include "utils/vec2.h"
#include "utils/rect2.h"
#include "FrameBuffer.h"

class AppState {
public:
    static std::unique_ptr<AppState> init_app();

    bool must_close() const;
    void handle_input();
    void render();
    void update();

    ~AppState();

private:
    // private constructor
    AppState();

    unsigned int m_width;
    unsigned int m_height;
    bool m_must_close_flag;
    uint64_t m_frame_counter;

    std::default_random_engine m_rng;    

    inline float random();
    inline char random_char(const char* palette);
    
    FrameBuffer* m_fb;
    
    // some fun animation stuff
    struct MovingPart {
        fvec2_t pos;
        fvec2_t vel;
        char pixel;
        int size;
        
        void update(irect2_t bounds);
        fvec2_t get_scaled_pos() const;
        
        std::array<fvec2_t, 3> get_vertices(float rotation = 0.0f, const fvec2_t& translation = {0.0f, 0.0f}) const;
    };
    
    static const int NUMBER_OF_MOVING_PARTS = 16;
    
    std::array<MovingPart, NUMBER_OF_MOVING_PARTS> m_moving_parts;
    
    // initialize moving parts with random positions and velocities within the bounds
    void initialize_moving_parts(irect2_t bounds);
};

#endif // APPSTATE_H
