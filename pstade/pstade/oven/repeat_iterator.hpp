#ifndef PSTADE_OVEN_REPEAT_ITERATOR_HPP
#define PSTADE_OVEN_REPEAT_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // advance, distance
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>


namespace pstade { namespace oven {


template< class ForwardIter, class SizeT >
struct repeat_iterator;


namespace repeat_iterator_detail {


    template< class ForwardIter, class SizeT >
    struct super_
    {
        typedef boost::iterator_adaptor<
            repeat_iterator<ForwardIter, SizeT>,
            ForwardIter
        > type;
    };

/*
    template< class SizeT >
    struct reverse_size
    {
        explicit reverse_size(SizeT index) :
            m_index(index)
        { }

        SizeT operator++()
        { return --m_index; }

        template< class SizeT_ >
        void operator+=(SizeT_ index)
        { m_index -= index; }

        SizeT base() const
        { return m_index; }

    private:
        SizeT m_index;
    };
*/

    template< class Difference, class ForwardIter, class SizeT >
    Difference pseudo_diff(ForwardIter it, SizeT index, ForwardIter first, ForwardIter last)
    {
        Difference srcSize = std::distance(first, last);
        Difference srcDiff = std::distance(first, it);
        return (srcSize * index) + srcDiff;
    }


    template< class ForwardIter, class SizeT >
    void increment(ForwardIter& it, SizeT& index, ForwardIter first, ForwardIter last)
    {
        BOOST_ASSERT(std::distance(first, last) >= 0);

        if (++it == last) {
            it = first;
            ++index;
        }
    }


    template< class ForwardIter, class SizeT >
    void decrement(ForwardIter& it, SizeT& index, ForwardIter first, ForwardIter last)
    {
        BOOST_ASSERT(std::distance(first, last) >= 0);

        if (it != first) {
            --it;
        }
        else {
            it = --last;
            --index;
        }
    }


} // namespace repeat_iterator_detail


template< class ForwardIter, class SizeT >
struct repeat_iterator :
    repeat_iterator_detail::super_<ForwardIter, SizeT>::type
{
private:
    typedef typename repeat_iterator_detail::super_<ForwardIter, SizeT>::type super_t;
    typedef typename super_t::difference_type diff_t;
    typedef typename super_t::reference ref_t;

public:
    explicit repeat_iterator()
    { }

    explicit repeat_iterator(ForwardIter it, SizeT index, ForwardIter first, ForwardIter last) :
        super_t(it), m_index(index),
        m_first(first), m_last(last)        
    { }

    template< class ForwardIter_, class SizeT_ >
    repeat_iterator(
        repeat_iterator<ForwardIter_, SizeT_> other,
        typename boost::enable_if_convertible<ForwardIter_, ForwardIter>::type * = 0,
        typename boost::enable_if_convertible<SizeT_, SizeT>::type * = 0
    ) :
        super_t(other.base()), m_index(other.index()),
        m_first(other.sbegin()), m_last(other.send())       
    { }

    const ForwardIter sbegin() const
    { return m_first; }

    const ForwardIter send() const
    { return m_last; }

    const SizeT index() const
    { return m_index; }

private:
    ForwardIter m_first, m_last;
    SizeT m_index;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(m_index >= 0);

        return *this->base();
    }

    void increment()
    {
        BOOST_ASSERT(m_index >= 0);

        repeat_iterator_detail::increment(this->base_reference(), m_index, m_first, m_last);

        BOOST_ASSERT(m_index >= 0);
    }

    void decrement()
    {
        BOOST_ASSERT(m_index >= 0);

        repeat_iterator_detail::decrement(this->base_reference(), m_index, m_first, m_last);

        BOOST_ASSERT(m_index >= 0);
    }

    bool equal(repeat_iterator other) const
    {
        BOOST_ASSERT(m_index >= 0);
        BOOST_ASSERT(
            m_first == other.sbegin() &&
            m_last == other.send() &&
            "incompatible iterators"
        );

        return
            this->base() == other.base() &&
            m_index == other.m_index
        ;
    }

    // seems stupid implementation...
    //
    void advance(diff_t d)
    {
        BOOST_ASSERT(m_index >= 0);

        if (d >= 0)
            advance_to_right(d);
        else
            advance_to_left(-d);

        BOOST_ASSERT(m_index >= 0);
    }

    void advance_to_right(diff_t d)
    {
        BOOST_ASSERT(d >= 0);

        diff_t srcSize = std::distance(m_first, m_last);
        diff_t srcDiff = std::distance(m_first, this->base());
        diff_t tmpDiff = srcDiff + d;
        this->base_reference() = m_first;
        std::advance(this->base_reference(), tmpDiff % srcSize);
        diff_t count = tmpDiff / srcSize;
        m_index += count;
    }

    void advance_to_left(diff_t d)
    {
        BOOST_ASSERT(d >= 0);

        diff_t srcSize = std::distance(m_first, m_last);
        diff_t srcDiff = std::distance(this->base(), m_last);
        diff_t tmpDiff = d + srcDiff;
        diff_t rem = (tmpDiff % srcSize);
        if (rem == 0) {
            this->base_reference() = m_first;
        }
        else {
            this->base_reference() = m_last;
            std::advance(this->base_reference(), -rem);
        }
        diff_t count = tmpDiff / srcSize;
        if (rem == 0)
            m_index -= (count - 1);
        else
            m_index -= count;
    }

    diff_t distance_to(repeat_iterator other) const
    {
        return 
            repeat_iterator_detail::pseudo_diff<diff_t>(other.base(), other.index(), other.sbegin(), other.send())
                - repeat_iterator_detail::pseudo_diff<diff_t>(this->base(), m_index, m_first, m_last)
        ;
    }
};


template< class ForwardIter, class SizeT > inline const
repeat_iterator<ForwardIter, SizeT>
make_repeat_iterator(ForwardIter it, SizeT index, ForwardIter first, ForwardIter last)
{
    return repeat_iterator<ForwardIter, SizeT>(it, index, first, last);
}


} } // namespace pstade::oven


#endif
