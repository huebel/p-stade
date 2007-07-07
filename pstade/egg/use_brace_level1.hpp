#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_USE_BRACE_LEVEL1_HPP
#define PSTADE_EGG_USE_BRACE_LEVEL1_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type.hpp>
#include "./config.hpp" // PSTADE_EGG_MAX_ARITY


namespace pstade { namespace egg {


    struct use_brace_level1
    {
        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/use_brace_level1.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class X, BOOST_PP_ENUM_PARAMS(n, class A)>
    X operator()(boost::type<X>, BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        X x = { { BOOST_PP_ENUM_PARAMS(n, a) } };
        return x;
    }
    

#undef n
#endif