#ifndef PSTADE_OVEN_CHECKED_HPP
#define PSTADE_OVEN_CHECKED_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/check_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace checked_detail {


    template< class Range >
    struct baby
    {
        typedef
            detail::check_iterator<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            return aux(boost::begin(rng), boost::end(rng));
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last) const
        {
            return result_type(iter_t(first, first, last), iter_t(last, first, last));
        }
    };


} // namespace checked_detail


PSTADE_FUNCTION(make_checked, (checked_detail::baby<_>))
PSTADE_PIPABLE(checked, (op_make_checked))


#if !defined(NDEBUG)
    #define PSTADE_OVEN_CHECKED(Rng) pstade::oven::make_checked(Rng)
#else
    #define PSTADE_OVEN_CHECKED(Rng) Rng
#endif


#if defined(PSTADE_OVEN_IN_BOOST)
    #define BOOST_OVEN_CHECKED PSTADE_OVEN_CHECKED
#endif


} } // namespace pstade::oven


#endif
