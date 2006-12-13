#ifndef PSTADE_SAUSAGE_YIELD_RANGE_HPP
#define PSTADE_SAUSAGE_YIELD_RANGE_HPP


// PStade.Sausage
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/object_generator.hpp>
#include <pstade/oven/as_lightweight_proxy.hpp>
#include <pstade/oven/iter_range.hpp>
#include <pstade/pipable.hpp>
#include "./yield_iterator.hpp"


namespace pstade { namespace sausage {


namespace yield_range_detail {


    template< class Routine >
    struct super_ :
        oven::iter_range<
            yield_iterator<Routine>
        >
    { };


} // namespace yield_range_detail


template< class Routine >
struct yield_range :
    yield_range_detail::super_<Routine>::type,
    private oven::as_lightweight_proxy< yield_range<Routine> >
{
    typedef yield_range type;

private:
    typedef typename yield_range_detail::super_<Routine>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit yield_range(Routine const& rou) :
        super_t(iter_t(rou), iter_t())
    { }
};


PSTADE_OBJECT_GENERATOR(make_yield_range,
    const(yield_range< deduce_to_value<from_1> >))
PSTADE_PIPABLE(yielded, (op_make_yield_range))


} } // namespace pstade::sausage


#endif
