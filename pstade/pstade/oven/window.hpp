#ifndef PSTADE_OVEN_WINDOW_HPP
#define PSTADE_OVEN_WINDOW_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/next_prior.hpp" // next
#include "./distance.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace window_detail {


    template< class Range, class, class >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef typename
            range_iterator<Range>::type
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Range& rng, diff_t const& n, diff_t const& m)
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));

            // Should a "bigger" window be allowed?
            // BOOST_ASSERT(0 <= n && n <= m && m <= distance(rng));

            iter_t first = detail::next(boost::begin(rng), n);
            return result(first, detail::next(first, m - n));
        }
    };


} // namespace window_detail


PSTADE_FUNCTION(make_window, (window_detail::baby<_, _, _>))
PSTADE_PIPABLE(window, (op_make_window))


} } // namespace pstade::oven


#endif
