#ifndef PSTADE_OVEN_ALWAYS_RANGE_HPP
#define PSTADE_OVEN_ALWAYS_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/egg/pipeline.hpp>
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class IgnoredRange, class Range >
struct always_range :
    sub_range_base<Range>::type,
    private lightweight_proxy< always_range<IgnoredRange, Range> >
{
    typedef Range pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(IgnoredRange, SinglePassRangeConcept);
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename sub_range_base<Range>::type super_t;

public:
    always_range(IgnoredRange& , Range& rng) :
        super_t(rng)
    { }
};


namespace always_range_detail {


    struct baby_generator
    {
        template< class Unused, class IgnoredRange, class Range >
        struct result
        {
            typedef always_range<IgnoredRange, Range> const type;
        };

        template< class Result, class IgnoredRange, class Range>
        Result call(IgnoredRange& _, Range& rng)
        {
            return Result(_, rng);
        }
    };


} // namespace always_range_detail


PSTADE_EGG_FUNCTION(make_always_range, always_range_detail::baby_generator)
PSTADE_EGG_PIPELINE(always,            always_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
