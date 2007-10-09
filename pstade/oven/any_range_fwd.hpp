#ifndef PSTADE_OVEN_ANY_RANGE_FWD_HPP
#define PSTADE_OVEN_ANY_RANGE_FWD_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/use_default_fwd.hpp"


namespace pstade { namespace oven {


template<
    class Reference,
    class Traversal,
    class Value      = boost::use_default,
    class Difference = boost::use_default
>
struct any_range;


template<
    class Reference,
    class Value      = boost::use_default,
    class Difference = boost::use_default
>
struct any_index_range;


} } // namespace pstade::oven


#endif
