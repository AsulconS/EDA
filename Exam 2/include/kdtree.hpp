#ifndef KD_TREE_HPP
#define KD_TREE_HPP

#include <algorithm.hpp>

#define DIMS 3

struct KDNode
{
    Point point;

    KDNode* left;
    KDNode* right;
};

class KDTree
{
public:
    KDTree(vector<Point>& points, uint8_t dims = DIMS);
    ~KDTree();

    void knn(const Point& query_point, WPointQueue& points_queue, uint8_t k = 8);

private:
    KDNode* m_root;
    uint8_t m_dims;

    void knn(KDNode* root, const Point& query_point, WPointQueue& points_queue, uint8_t k, uint8_t depth = 0);

    void destroyKDTree(KDNode* root);
    KDNode* buildKDTree(vector<Point>& points, int l, int r, uint8_t depth = 0);
};

#endif // KD_TREE_HPP
