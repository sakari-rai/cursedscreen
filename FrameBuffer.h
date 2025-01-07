#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "utils/vec2.h"
#include "utils/rect2.h"
#include <curses.h>

class FrameBuffer {
public:
    FrameBuffer(unsigned int width, unsigned int height);
    ~FrameBuffer();
    
    void set_pixel(unsigned int x, unsigned int y, char value);
    void draw_line(const ivec2_t& a, const ivec2_t& b, char pixel);
    void draw_vertical_line(unsigned int x, unsigned int y0, unsigned int y1, char pixel);
    void draw_horizontal_line(unsigned int x0, unsigned int x1, unsigned int y, char pixel);
    void draw_filled_triangle(const ivec2_t& a, const ivec2_t& b, const ivec2_t& c, char pixel);
    void clear(char pixel);
    void render(WINDOW* dst, irect2_t clip);

private:
    unsigned int m_width;
    unsigned int m_height;
    char* m_buffer;
};

#endif // FRAMEBUFFER_H
