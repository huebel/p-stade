#ifndef PSTADE_OVEN_FILTER_RANGE_HPP
#define PSTADE_OVEN_FILTER_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/filter_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


namespace filter_range_detail {


    template< class Range, class Predicate >
    struct super_
    {
        typedef boost::iterator_range<
            boost::filter_iterator<
                Predicate,
                typename boost::range_result_iterator<Range>::type
            >
        > type;
    };


} // namespace filter_range_detail


template< class Range, class Predicate >
struct filter_range :
    filter_range_detail::super_<Range, Predicate>::type
{
private:
    typedef typename filter_range_detail::super_<Range, Predicate>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    filter_range(Range& rng, Predicate pred) :
        super_t(
            iter_t(pred, boost::begin(rng), boost::end(rng)),
            iter_t(pred, boost::end(rng), boost::end(rng))
        )
    { }

};


namespace filter_range_detail {


    struct baby_generator
    {
        template< class Range, class Predicate >
        struct result
        {
            typedef typename boost::remove_cv<Predicate>::type pred_t;
            typedef const filter_range<Range, pred_t> type;
        };

        template< class Result, class Range, class Predicate >
        Result call(Range& rng, Predicate pred)
        {
            return Result(rng, pred);
        }
    };


} // namespace filter_range_detail


PSTADE_EGG_FUNCTION(make_filter_range, filter_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(filtered, filter_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::filter_range, 2)


#endif
