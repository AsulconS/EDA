#include <algorithm.hpp>

PointComp::PointComp(const uint8_t axis)
    : m_axis {axis}
{
}

bool PointComp::operator() (const Point& l, const Point& r) const
{
    return l[m_axis] < r[m_axis];
}

void swap(Point& v1, Point& v2)
{
    Point temp = std::move(v1);
    v1 = std::move(v2);
    v2 = std::move(temp);
}

int partition(vector<Point>& data, int l, int r, const PointComp& comp)
{
    int i = l - 1;
    for(int j = l; j < r; ++j)
    {
        if(comp(data[j], data[r]))
        {
            swap(data[++i], data[j]);
        }
    }
    swap(data[i + 1], data[r]);
    return i + 1;
}

int randPartition(vector<Point>& data, int l, int r, const PointComp& comp)
{
    int pivot = rand() % (r - l + 1);
    swap(data[l + pivot], data[r]);
    return partition(data, l, r, comp);
}

Point& findMedian(vector<Point>& data, int l, int r, const PointComp& comp)
{
    int n {r - l + 1};

    int k {l + n / 2};
    int q {};
    while(true)
    {
        q = randPartition(data, l, r, comp);
        if(q == k)
        {
            return data[k];
        }

        if(q < k)
        {
            l = q + 1;
        }
        else
        {
            r = q - 1;
        }
    }
}
