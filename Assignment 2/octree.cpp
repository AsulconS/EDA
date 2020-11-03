#include <octree.hpp>

uint8_t Octree::s_path_buffer[8] {};

Octree::Octree(const uint8_t t_color_depth)
    : m_root        {new ColorNode {{0, 0, 0}, 0, {}}},
      m_color_depth {t_color_depth}
{
}

Octree::~Octree()
{
    remove(m_root);
}

void Octree::reduction(const uint8_t levels)
{
    for(uint8_t i = 0; i < levels; ++i)
    {
        if(m_color_depth > 0)
        {
            reduct(m_root);
            --m_color_depth;
        }
    }
}

void Octree::getPalette(std::vector<Color>& palette)
{
    pushColors(m_root, palette);
}

void Octree::insertColor(const Color& color)
{
    uint32_t rbit {};
    uint32_t gbit {};
    uint32_t bbit {};
    for(uint8_t i = 0; i < m_color_depth; ++i)
    {
         rbit = (color.r & (0x80 >> i)) >> (0x7 - i);
         gbit = (color.g & (0x80 >> i)) >> (0x7 - i);
         bbit = (color.b & (0x80 >> i)) >> (0x7 - i);
         s_path_buffer[i] = (rbit << 0x2) | (gbit << 0x1) | bbit;
    }

    ColorNode* current_node {m_root};
    for(uint8_t i = 0; i < m_color_depth; ++i)
    {
        if(current_node->children[s_path_buffer[i]] == nullptr)
        {
            current_node->children[s_path_buffer[i]] = new ColorNode {{0, 0, 0}, false, 0, {}};
        }
        current_node = current_node->children[s_path_buffer[i]];
    }
    current_node->color.r += color.r;
    current_node->color.g += color.g;
    current_node->color.b += color.b;
    current_node->is_leaf  = true;
    ++current_node->pixel_count;
}

Color Octree::getProcessedColor(const Color& color)
{
    uint32_t rbit {};
    uint32_t gbit {};
    uint32_t bbit {};
    for(uint8_t i = 0; i < m_color_depth; ++i)
    {
         rbit = (color.r & (0x80 >> i)) >> (0x7 - i);
         gbit = (color.g & (0x80 >> i)) >> (0x7 - i);
         bbit = (color.b & (0x80 >> i)) >> (0x7 - i);
         s_path_buffer[i] = (rbit << 0x2) | (gbit << 0x1) | bbit;
    }

    printf("m_color_depth: %d ", m_color_depth);
    ColorNode* current_node {m_root};
    for(uint8_t i = 0; i < m_color_depth; ++i)
    {
        current_node = current_node->children[s_path_buffer[i]];
    }
    Color cret {current_node->color};
    cret.r /= current_node->pixel_count;
    cret.g /= current_node->pixel_count;
    cret.b /= current_node->pixel_count;
    return cret;
}

void Octree::remove(ColorNode* node)
{
    for(uint8_t i = 0; i < 8; ++i)
    {
        if(node->children[i] != nullptr)
        {
            remove(node->children[i]);
        }
    }
    delete node;
}

void Octree::reduct(ColorNode* node)
{
    Color color_sum {0, 0, 0};
    uint32_t pixel_count {0};

    bool has_leafs {false};
    for(uint8_t i = 0; i < 8; ++i)
    {
        if(node->children[i] != nullptr)
        {
            if(node->children[i]->is_leaf)
            {
                has_leafs = true;
                color_sum.r += node->children[i]->color.r;
                color_sum.g += node->children[i]->color.g;
                color_sum.b += node->children[i]->color.b;
                pixel_count += node->children[i]->pixel_count;
            }
            else
            {
                reduct(node->children[i]);
            }
        }
    }
    if(has_leafs)
    {
        for(uint8_t i = 0; i < 8; ++i)
        {
            if(node->children[i] != nullptr)
            {
                delete node->children[i];
                node->children[i] = nullptr;
            }
        }
        node->color = color_sum;
        node->is_leaf = true;
        node->pixel_count = pixel_count;
    }
}

void Octree::pushColors(ColorNode* root, std::vector<Color>& colors)
{
    if(root->is_leaf)
    {
        uint32_t pixel_count = root->pixel_count;
        colors.push_back({root->color.r / pixel_count, root->color.g / pixel_count, root->color.b / pixel_count});
        return;
    }
    for(uint8_t i = 0; i < 8; ++i)
    {
        if(root->children[i] != nullptr)
        {
            pushColors(root->children[i], colors);
        }
    }
}
