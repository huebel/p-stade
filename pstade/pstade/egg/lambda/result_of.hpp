#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_LAMBDA_RESULT_OF_HPP
#define PSTADE_EGG_LAMBDA_RESULT_OF_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright Yusuke Kajimoto 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/apple/boost/result_of_fwd.hpp>
#include <pstade/preprocessor.hpp>
#include "../detail/meta_arg.hpp"
#include "./config.hpp"
#include "./functor_fwd.hpp"


namespace boost {


// 0ary
    template<class T>
    struct result_of<lambda::lambda_functor<T>(void)> : // CWPro8 requires 'void'.
        lambda::lambda_functor<T>::template sig<
            tuples::tuple<
                lambda::lambda_functor<T>
            >
        >
    { };

    template<class T>
    struct result_of<lambda::lambda_functor<T> const(void)> :
        result_of<lambda::lambda_functor<T>()>
    { };


// 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_LAMBDA_FUNCTOR_MAX_ARITY, <pstade/egg/lambda/result_of.hpp>))
    #include BOOST_PP_ITERATE()


} // namespace boost


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class T, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result_of<lambda::lambda_functor<T>(BOOST_PP_ENUM_PARAMS(n, A))> :
        lambda::lambda_functor<T>::template sig<
            tuples::tuple<
                lambda::lambda_functor<T>,
#if defined(PSTADE_EGG_LAMBDA_PERFECT_FUNCTORS)
                PSTADE_PP_ENUM_PARAMS_WITH(n, typename pstade::egg::detail::meta_arg<A, >::type &)
#else
                BOOST_PP_ENUM_PARAMS(n, A)
#endif
            >
        >
    { };

    template<class T, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result_of<lambda::lambda_functor<T> const(BOOST_PP_ENUM_PARAMS(n, A))> :
        result_of<lambda::lambda_functor<T>(BOOST_PP_ENUM_PARAMS(n, A))>
    { };


#undef n
#endif
