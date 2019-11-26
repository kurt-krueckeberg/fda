#ifndef overwrite_iter_h
#define  overwriter_iter_h

#include <iterator>

template<class Cont>
    class overwrite_iterator { 
public:
     
    //typedef Cont container_type;
    // typedef Cont::value_type value_type;
    using container_type = Cont;
    using value_type = Cont::value_type;
    using reference = value_type&;
    using pointer = value_type*;
    using iterator_category = std::output_iterator_tag;

    explicit overwrite_iterator(Cont& x)
        : cont(x), iter(x.begin())     {}

    overwrite_iterator(Cont& x, Cont::iterator it)
        : cont(x), iter(it)     {}

    overwrite_iterator& operator=(const Cont::value_type& val)
    {
        iter == cont.end() ? cont.push_back(val) 
                                 : (*iter = val, ++iter);
        return *this;
    }

    overwrite_iterator& operator*()
    {
        return *this;
    }

    overwrite_iterator& operator++()
    {
        return *this;
    }

    overwrite_iterator operator++(int)
    {
        return *this;
    }

    operator Cont::iterator()
    {
        return iter;
    }
protected:
    Cont& cont;
    Cont::iterator iter;
    };


template<class Cont>
overwrite_iterator<Cont> overwriter(Cont& x) 
{
    return overwrite_iterator<Cont>(x);
}

template<class Cont>
overwrite_iterator<Cont> overwriter(Cont& x, Cont::iterator it) 
{
    return overwrite_iterator<Cont>(x, it);
}
#endif
