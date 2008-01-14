#ifndef BOOST_EGG_DETAIL_CALL_LITTLE_IMPL_FWD_HPP
#define BOOST_EGG_DETAIL_CALL_LITTLE_IMPL_FWD_HPP
#include "./prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/pstade/enable_if.hpp>


namespace pstade { namespace egg {


    // Little_ is guaranteed to be complete when call_little_impl instantiated,
    // because this is instantiated only in function body.
    template<class Little_, class Result, class EnableIf = enabler>
    struct call_little_impl;


} } // namespace pstade::egg


#endif
