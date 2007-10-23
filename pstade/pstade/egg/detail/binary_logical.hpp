#ifndef PSTADE_EGG_DETAIL_BINARY_LOGICAL_HPP
#define PSTADE_EGG_DETAIL_BINARY_LOGICAL_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/make_bool.hpp>
#include <pstade/pod_constant.hpp>


#define PSTADE_EGG_BINARY_LOGICAL(F, Op) \
    struct BOOST_PP_CAT(T_, F) \
    { \
        typedef bool result_type; \
        \
        template<class X, class Y> \
        bool operator()(X const& x, Y const& y) const \
        { \
            return pstade::make_bool(x) Op pstade::make_bool(y); \
        } \
    }; \
    \
    PSTADE_ADL_BARRIER(F) { \
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_, F)), F) = {}; \
    } \
/**/


#endif