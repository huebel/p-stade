#ifndef PSTADE_OVEN_TEST_PROXIES_HPP
#define PSTADE_OVEN_TEST_PROXIES_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../detail/prelude.hpp"
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "../concepts.hpp"
#include "../iter_range.hpp"
#include "../range_iterator.hpp"
#include "./proxy_iterator.hpp"


namespace pstade { namespace oven { namespace test {


template< class Range >
struct baby_make_proxies
{
    typedef
        proxy_iterator<
            typename range_iterator<Range>::type
        >
    iter_t;

    typedef
        iter_range<iter_t> const
    result_type;

    result_type operator()(Range& rng) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        return result_type(rng);
    }
};


PSTADE_FUNCTION(make_proxies, (baby_make_proxies<_>))
PSTADE_PIPABLE(proxies, (op_make_proxies))


} } } // namespace pstade::oven::test


#endif
