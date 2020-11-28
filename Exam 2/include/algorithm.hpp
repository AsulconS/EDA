#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <cmath>
#include <cstdint>

#include <vector>
#include <random>
#include <utility>
#include <algorithm>

#include <iostream>

#include <depq.hpp>

using std::pair;
using std::vector;
using Point = vector<double>;
using WPoint = pair<Point, double>;

class PointComp
{
public:
    PointComp(const uint8_t axis);
    bool operator() (const Point& l, const Point& r) const;

private:
    uint8_t m_axis;
};

class WPointComp
{
public:
    bool operator() (const WPoint& l, const WPoint& r) const;
};

using WPointQueue = DEPQ<WPoint, WPointComp>;

void swap(Point& v1, Point& v2);
int partition(vector<Point>& data, int l, int r, const PointComp& comp);
int randPartition(vector<Point>& data, int l, int r, const PointComp& comp);
Point& findMedian(vector<Point>& data, int l, int r, const PointComp& comp);

double distance(const Point& p1, const Point& p2, uint8_t dims);

#endif // ALGORITHM_HPP
