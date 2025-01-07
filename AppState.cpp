#include "AppState.h"
#include <chrono>

std::unique_ptr<AppState> AppState::init_app() {
    initscr();
    raw();
    keypad(stdscr, TRUE); // Enable function keys
    nodelay(stdscr, TRUE); // Non-blocking input for stdscr
    noecho(); // Do not echo input characters
    return std::unique_ptr<AppState>(new AppState());
}

bool AppState::must_close() const {
    return m_must_close_flag;
}

void AppState::handle_input() {
    int ch = wgetch(stdscr);
    
    switch (ch) {
        case 'q':
            m_must_close_flag = true;
            break;
        default:
            break;
    }
}

void AppState::update() {
    for (auto& part : m_moving_parts) {
        part.update(irect2_t{1, 1, 
            static_cast<int>(m_width - 2),
            static_cast<int>(m_height - 2)});
    }
}

void AppState::render() {
    wclear(stdscr);
    box(stdscr, 0, 0);

    mvwprintw(stdscr, 0, 1, "Frame count = %d", m_frame_counter++); 
    
    m_fb->clear(' ');

    // draw moving parts as triangles rotated by the velocity angle
    for (const auto& part : m_moving_parts) {
        // calculate velocity angle using atan2
        const float angle = std::atan2(part.vel.y, part.vel.x);
        auto vertices = part.get_vertices(angle, part.get_scaled_pos());
        m_fb->draw_filled_triangle(vertices[0].to_ivec2(), vertices[1].to_ivec2(), vertices[2].to_ivec2(), part.pixel);
    }
    
    m_fb->render(stdscr, irect2_t{1, 1, 
        static_cast<int>(m_width - 2),
        static_cast<int>(m_height - 2)});

    wrefresh(stdscr);
}

AppState::~AppState() {
    // cleanup curses window and reset console
    endwin();
    
    delete m_fb;
}

// private constructor
AppState::AppState() : m_must_close_flag{false}, m_frame_counter{0}, 
    m_rng(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())) {
    getmaxyx(stdscr, m_height, m_width);
    m_fb = new FrameBuffer(m_width, m_height);
    initialize_moving_parts(irect2_t{1, 1, 
        static_cast<int>(m_width - 2),
        static_cast<int>(m_height - 2)});
}

inline float AppState::random() {
    return std::uniform_real_distribution<float>(0.0f, 1.0f)(m_rng); 
}

inline char AppState::random_char(const char* palette) {
    return palette[static_cast<int>(random() * strlen(palette))];
}

// MovingPart methods
void AppState::MovingPart::update(irect2_t bounds) {
    // update position
    pos += vel;

    // check bounds collision
    if (pos.x < bounds.topLeft().x) {
        pos.x = bounds.topLeft().x;
        vel.x = -vel.x;
    } else if (pos.x > bounds.bottomRight().x) {
        pos.x = bounds.bottomRight().x;
        vel.x = -vel.x;
    }
    
    if (pos.y < bounds.topLeft().y) {
        pos.y = bounds.topLeft().y;
        vel.y = -vel.y;
    } else if (pos.y > bounds.bottomRight().y) {
        pos.y = bounds.bottomRight().y;
        vel.y = -vel.y;
    }
}

fvec2_t AppState::MovingPart::get_scaled_pos() const {
    return pos;
}

// initialize moving parts with random positions and velocities within the bounds
void AppState::initialize_moving_parts(irect2_t bounds) {
    for (auto& part : m_moving_parts) {
        part.pos = fvec2_t{random() * bounds.width(), random() * bounds.height()};

        part.vel = fvec2_t{random() * 10 - 5, random() * 10 - 5};
        
        // ensure velocity is not zero
        if (part.vel.isZero()) {
            part.vel = fvec2_t{1, 1};
        }

        part.pixel = '#'; //random_char(".,-~:;=!*#$@");
    }
}

// get vertices of the triangle rotated by the given angle in degrees
std::array<fvec2_t, 3> AppState::MovingPart::get_vertices(float rotation, const fvec2_t& translation) const {
    // vertices of an equilateral triangle
    std::array<fvec2_t, 3> vertices = {
        fvec2_t{1.0f, 0},
        fvec2_t{-0.5f, -0.5f},
        fvec2_t{-0.5f, 0.5f}
    };

    // rotate the vertices by the given angle using fvec2_t rotation methods
    for (auto& vertex : vertices) {
        vertex.rotate(rotation);
        vertex += translation;
    }
    
    return vertices;
}