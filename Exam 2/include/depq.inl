template <typename T, typename Compare>
inline int DEPQ<T, Compare>::size()
{
    return m_s.size();
}

template <typename T, typename Compare>
inline bool DEPQ<T, Compare>::empty()
{
    return !m_s.size();
}

template <typename T, typename Compare>
inline void DEPQ<T, Compare>::push(const T& x)
{
    m_s.insert(x);
}

template <typename T, typename Compare>
inline T DEPQ<T, Compare>::top()
{
    return *m_s.begin();
}

template <typename T, typename Compare>
inline T DEPQ<T, Compare>::bottom()
{
    return *m_s.rbegin();
}

template <typename T, typename Compare>
inline void DEPQ<T, Compare>::pop_top()
{
    if(!m_s.size())
        return;
    m_s.erase(m_s.begin());
}

template <typename T, typename Compare>
inline void DEPQ<T, Compare>::pop_bottom()
{
    if(!m_s.size())
        return;
    auto it {m_s.end()};
    --it;
    m_s.erase(it);
}
