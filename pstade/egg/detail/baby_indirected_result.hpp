#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_BABY_INDIRECTED_RESULT_HPP
#define PSTADE_OVEN_BABY_INDIRECTED_RESULT_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../config.hpp" // PSTADE_EGG_MAX_ARITY
#include "../indirect.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Indirectable>
    struct indirectable_base :
        boost::remove_reference<
            typename result_of<op_indirect(Indirectable const&)>::type
        >
    { };


    template<class Indirectable>
    struct baby_indirected_result
    {
        Indirectable m_ind;

        typedef typename indirectable_base<Indirectable>::type base_type;

        typename result_of<op_indirect(Indirectable const&)>::type
        base() const
        {
            return *m_ind;
        }

    // 0ary
        typedef typename
            result_of<typename indirectable_base<Indirectable>::type()>::type
        nullary_result_type;

        template<class Result>
        Result call() const
        {
            return (*m_ind)();
        }

    // 1ary-
        template<class Myself, PSTADE_EGG_APPLY_PARAMS(A)>
        struct apply { };

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/detail/baby_indirected_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<base_type(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))>
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return (*m_ind)(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
