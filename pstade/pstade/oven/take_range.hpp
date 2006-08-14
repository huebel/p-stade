#ifndef PSTADE_OVEN_TAKE_RANGE_HPP
#define PSTADE_OVEN_TAKE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipeline.hpp>
#include "./detail/advance_begin.hpp"
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_difference.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class ForwardRange >
struct take_range :
    sub_range_base<ForwardRange>::type,
    private lightweight_proxy< take_range<ForwardRange> >
{
    typedef ForwardRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeConcept);
    typedef typename sub_range_base<ForwardRange>::type super_t;
    typedef typename range_difference<ForwardRange>::type diff_t;

public:
    take_range(ForwardRange& rng, diff_t d) :
        super_t(boost::begin(rng), detail::advance_begin(rng, d))
    { }
};


namespace take_range_detail {


    struct baby_generator
    {
        template< class Unused, class ForwardRange, class Difference >
        struct result
        {
            typedef take_range<ForwardRange> const type;
        };

        template< class Result, class ForwardRange, class Difference >
        Result call(ForwardRange& rng, Difference d)
        {
            return Result(rng, d);
        }
    };


} // namespace take_range_detail


PSTADE_EGG_FUNCTION(make_take_range, take_range_detail::baby_generator)
PSTADE_EGG_PIPELINE(taken,           take_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
