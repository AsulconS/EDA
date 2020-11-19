#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <random>
#include <vector>
#include <utility>

using std::vector;
using Point = vector<uint64_t>;

class PointComp
{
public:
    PointComp(const uint8_t axis);
    bool operator() (const Point& l, const Point& r) const;

private:
    uint8_t m_axis;
};

void swap(Point& v1, Point& v2);
int partition(vector<Point>& data, int l, int r, const PointComp& comp);
int randPartition(vector<Point>& data, int l, int r, const PointComp& comp);
Point& findMedian(vector<Point>& data, int l, int r, const PointComp& comp);

#endif // ALGORITHM_HPP
