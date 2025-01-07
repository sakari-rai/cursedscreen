#include "FrameBuffer.h"
#include <algorithm>
#include <cstring>

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height) : m_width{width}, m_height{height} {
    m_buffer = new char[width * height];
}

FrameBuffer::~FrameBuffer() {
    delete[] m_buffer;
}

void FrameBuffer::set_pixel(unsigned int x, unsigned int y, char value) {
    if (x < m_width && y < m_height) {
        m_buffer[y * m_width + x] = value;
    }
}

void FrameBuffer::draw_line(const ivec2_t& a, const ivec2_t& b, char pixel) {
    const int dx = abs(b.x - a.x);
    const int dy = abs(b.y - a.y);
    const int sx = a.x < b.x ? 1 : -1;
    const int sy = a.y < b.y ? 1 : -1;
    int err = dx - dy;
    int x = a.x;
    int y = a.y;
    while (true) {
        set_pixel(x, y, pixel);
        if (x == b.x && y == b.y) {
            break;
        }
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    } 
}

void FrameBuffer::draw_vertical_line(unsigned int x, unsigned int y0, unsigned int y1, char pixel) {
    for (unsigned int y = y0; y <= y1; ++y) {
        set_pixel(x, y, pixel);
    }
}

void FrameBuffer::draw_horizontal_line(unsigned int x0, unsigned int x1, unsigned int y, char pixel) {
    for (unsigned int x = x0; x <= x1; ++x) {
        set_pixel(x, y, pixel);
    }
}

void FrameBuffer::draw_filled_triangle(const ivec2_t& a, const ivec2_t& b, const ivec2_t& c, char pixel) {
    // Sort vertices by y-coordinate
    ivec2_t v1 = a, v2 = b, v3 = c;
    if (v1.y > v2.y) std::swap(v1, v2);
    if (v2.y > v3.y) std::swap(v2, v3);
    if (v1.y > v2.y) std::swap(v1, v2);

    auto edge_interpolate = [](const ivec2_t& v1, const ivec2_t& v2, int y) {
        if (v1.y == v2.y) return v1.x;
        return v1.x + (v2.x - v1.x) * (y - v1.y) / (v2.y - v1.y);
    };
 
    for (int y = v1.y; y <= v3.y; ++y) {
        if (y < v2.y) {
            int x1 = edge_interpolate(v1, v3, y);
            int x2 = edge_interpolate(v1, v2, y);
            if (x1 > x2) std::swap(x1, x2);
            for (int x = x1; x <= x2; ++x) {
                set_pixel(x, y, pixel);
            }
        } else {
            int x1 = edge_interpolate(v1, v3, y);
            int x2 = edge_interpolate(v2, v3, y);
            if (x1 > x2) std::swap(x1, x2);
            for (int x = x1; x <= x2; ++x) {
                set_pixel(x, y, pixel);
            }
        }
    }
}

void FrameBuffer::clear(char pixel) {
    std::memset(m_buffer, pixel, m_width * m_height);
}

void FrameBuffer::render(WINDOW* dst, irect2_t clip) {
    const auto tl = clip.topLeft(); 
    const auto br = clip.bottomRight();
    for(unsigned int y = tl.y; y < br.y; y++) {
        for(unsigned int x = tl.x; x < br.x; x++) {
            mvwaddch(dst, y, x, m_buffer[y * m_width + x]);
        }
    }
}
