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

void KDTree::knn(const Point& query_point, WPointQueue& points_queue, uint8_t k)
{
    knn(m_root, query_point, points_queue, k);
}

void KDTree::knn(KDNode* root, const Point& query_point, WPointQueue& points_queue, uint8_t k, uint8_t depth)
{
    if(root == nullptr)
    {
        return;
    }

    double pdistance {distance(root->point, query_point, m_dims)};
    if(points_queue.size() < k)
    {
        points_queue.push(std::make_pair(root->point, pdistance));
    }
    else if(pdistance < points_queue.bottom().second)
    {
        points_queue.pop_bottom();
        points_queue.push(std::make_pair(root->point, pdistance));
    }
    uint8_t axis {(uint8_t)(depth % m_dims)};
    KDNode* next_branch {nullptr};
    KDNode* oppt_branch {nullptr};

    if(query_point[axis] < root->point[axis])
    {
        next_branch = root->left;
        oppt_branch = root->right;
    }
    else
    {
        next_branch = root->right;
        oppt_branch = root->left;
    }

    knn(next_branch, query_point, points_queue, k, depth + 1);
    if(points_queue.size() < k || abs(query_point[axis] - root->point[axis]) < points_queue.top().second)
    {
        knn(oppt_branch, query_point, points_queue, k, depth + 1);
    }
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
    Point& median = findMedian(points, l, r, PointComp {(uint8_t)(depth % m_dims)});
    KDNode* root  = new KDNode {median, nullptr, nullptr};
    root->left = buildKDTree(points, l, m - 1, depth + 1);
    root->right = buildKDTree(points, m + 1, r, depth + 1);

    return root;
}
