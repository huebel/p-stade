#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_FUNTION_BY_VALUE_HPP
#define PSTADE_EGG_FUNTION_BY_VALUE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A "movable type" like 'auto_ptr' must be called by value.
// "./function.hpp" makes rvalue unmovable.


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include "./config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./detail/nullary_result.hpp"
#include "./detail/sig.hpp"
#include "./nullary_result_of.hpp"


namespace pstade { namespace egg {


    template<class Baby>
    struct function_by_value
    {
        typedef Baby baby_type;

        Baby m_baby;

        Baby baby() const
        {
            return m_baby;
        }

    // 0ary
        typedef typename
            detail::nullary_result<Baby, function_by_value>::type
        nullary_result_type;

        nullary_result_type operator()() const
        {
            return m_baby.template call<
                nullary_result_type
            >();
        }

    // 1ary-
        template<class FunCall>
        struct result;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/function_by_value.hpp>))
        #include BOOST_PP_ITERATE()

        #include PSTADE_EGG_SIG()
    };


} } // namespace pstade::egg


PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(pstade::egg::function_by_value, 1)


#endif
#else
#define n BOOST_PP_ITERATION()


private:
    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    struct BOOST_PP_CAT(result, n) :
        Baby::template apply<
            Baby,
            BOOST_PP_ENUM_PARAMS(n, A)
        >
    { };

public:
    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<
            PSTADE_PP_ENUM_PARAMS_WITH(n, typename pass_by_value<A, >::type)
        >
    { };

    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    typename BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, a)) const
    {
        return m_baby.template call<
            typename BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>::type
        >(BOOST_PP_ENUM_PARAMS(n, a));
    }
    

#undef n
#endif
