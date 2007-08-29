#ifndef PSTADE_EGG_RET_HPP
#define PSTADE_EGG_RET_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/baby_ret_result.hpp"
#include "./function.hpp"
#include "./generator.hpp"
#include "./specified.hpp"
#include "./use_brace_level1.hpp"


namespace pstade { namespace egg {


    template<class Base, class ResultType = boost::use_default>
    struct result_of_ret
    {
        typedef
            function< detail::baby_ret_result<Base, ResultType> >
        type;
    };


    #define PSTADE_EGG_RET_L { {
    #define PSTADE_EGG_RET_R } }


    template<class ResultType = boost::use_default>
    struct tp_ret :
        generator<
            typename result_of_ret<deduce<boost::mpl::_1, as_value>, ResultType>::type,
            use_brace_level1
        >
    { };


    template<class ResultType = boost::use_default>
    struct xp_ret :
        tp_ret<ResultType>::type
    { };


    PSTADE_EGG_SPECIFIED1(ret, xp_ret, (class))


} } // namespace pstade::egg


#endif