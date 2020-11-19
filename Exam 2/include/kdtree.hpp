#ifndef KD_TREE_HPP
#define KD_TREE_HPP

#include <cstdint>

#include <queue>
#include <vector>
#include <algorithm>

#include <algorithm.hpp>

#define DIMS 3

using std::vector;
using Point = vector<uint64_t>;

struct KDNode
{
    uint8_t axis;
    Point point;

    KDNode* left;
    KDNode* right;
};

class KDTree
{
public:
    KDTree(vector<Point>& points, uint8_t dims = DIMS);
    ~KDTree();

    void knn();

private:
    KDNode* m_root;
    uint8_t m_dims;

    void destroyKDTree(KDNode* root);
    KDNode* buildKDTree(vector<Point>& points, int l, int r, uint8_t depth = 0);
};

#endif // KD_TREE_HPP
