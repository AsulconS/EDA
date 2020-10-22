#ifndef OCTREE_HPP
#define OCTREE_HPP

#include <cstdint>
#include <cstring>

#include <cstdio>

struct Color
{
    uint32_t r;
    uint32_t g;
    uint32_t b;
};

struct ColorNode
{
    Color color;
    bool is_leaf;
    uint32_t pixel_count;

    ColorNode* children[8];
};

class Octree
{
public:
    Octree(const uint8_t t_color_depth = 8);
    ~Octree();

    void reduction(const uint8_t levels = 1);

    void insertColor(const Color& color);
    Color getProcessedColor(const Color& color);

private:
    ColorNode* m_root;
    uint8_t m_color_depth;
    static uint8_t s_path_buffer[8];

    void remove(ColorNode* node);
    void reduct(ColorNode* node);
};

#endif
