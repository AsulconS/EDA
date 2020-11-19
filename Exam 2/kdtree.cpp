#include <kdtree.hpp>

KDTree::KDTree(vector<Point>& points, uint8_t dims)
    : m_root {nullptr},
      m_dims {dims}
{
    m_root = buildKDTree(points, 0, points.size() - 1);
}

KDTree::~KDTree()
{
    destroyKDTree(m_root);
}

void KDTree::destroyKDTree(KDNode* root)
{
    if(root == nullptr)
    {
        return;
    }
    destroyKDTree(root->left);
    destroyKDTree(root->right);
    delete root;
}

KDNode* KDTree::buildKDTree(vector<Point>& points, int l, int r, uint8_t depth)
{
    if(l > r)
    {
        return nullptr;
    }

    int n {r - l + 1};
    int m {l + n / 2};
    Point& median = findMedian(points, points.size(), PointComp {depth % m_dims});
    KDNode* root  = new KDNode {depth % m_dims, std::move(median), nullptr, nullptr};
    root->left = buildKDTree(points, 0, m - 1, depth + 1);
    root->right = buildKDTree(points, m + 1, r, depth + 1);

    return root;
}
