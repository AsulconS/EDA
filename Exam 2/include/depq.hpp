#ifndef DEPQ_HPP
#define DEPQ_HPP

#include <set>
#include <functional>

using std::set;
using std::less;

template <typename T, typename Compare = less<T>>
class DEPQ
{
public:
    int size();
    bool empty();
    void push(const T& x);

    T top();
    T bottom();

    void pop_top();
    void pop_bottom();

private:
    set<T, Compare> m_s;
};

#include <depq.inl>
#endif // DEPQ_HPP
