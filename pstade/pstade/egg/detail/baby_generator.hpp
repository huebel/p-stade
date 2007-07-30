#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_BABY_GENERATOR_HPP
#define PSTADE_EGG_DETAIL_BABY_GENERATOR_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/affect.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/use_default.hpp>
#include "../apply_params.hpp"
#include "../config.hpp" // PSTADE_EGG_MAX_ARITY
#include "../use_constructor.hpp"
#include "./template_arguments.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Lambda>
    struct is_placeholder_expression :
        boost::mpl::is_lambda_expression<Lambda>
    { };


    // Work around "ETI" of 'boost::mpl::apply'.

    template<class Lambda>
    struct to_alternative :
        boost::mpl::eval_if< is_placeholder_expression<Lambda>,
            detail::template_arguments_of<Lambda>,
            boost::mpl::identity<Lambda>
        >
    { };

    template<class Alternative, class Lambda>
    struct alternative_to :
        boost::mpl::eval_if< is_placeholder_expression<Lambda>,
            detail::template_arguments_copy<Alternative, Lambda>,
            boost::mpl::identity<Alternative>
        >
    { };


    template<
        class Lambda,
        PSTADE_PP_ENUM_PARAMS_WITH(PSTADE_EGG_MAX_ARITY, class A, = void)
    >
    struct generated_object
    {
        typedef typename
            boost::remove_cv<Lambda>::type // MPL needs this.
        lambda_t;

        typedef typename
            boost::mpl::BOOST_PP_CAT(apply, PSTADE_EGG_MAX_ARITY)<
                typename to_alternative<lambda_t>::type,
                BOOST_PP_ENUM_PARAMS(PSTADE_EGG_MAX_ARITY, A)
            >::type
        alt_object_t;

        typedef typename
            affect<Lambda, typename alternative_to<alt_object_t, lambda_t>::type>::type
        type;
    };


    // Even if using 'to_alternative', 'NullaryResult' must be explicitly specified.
    // E.g. 'my< some_metafunction<_1> >' where 'some_metafunction<void>::type' is ill-formed.

    template<
        class Lambda,
        class How           = boost::use_default,
        class NullaryResult = boost::use_default
    >
    struct baby_generator
    {
        typedef typename
            if_use_default<How, use_constructor>::type
        how_t;

    // 0ary
        typedef NullaryResult nullary_result_type;

        template<class Result>
        Result call() const
        {
            return Result();
        }

     // 1ary-
        template<class Myself, PSTADE_EGG_APPLY_PARAMS(A)>
        struct apply { }; // msvc warns if incomplete.

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/detail/baby_generator.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        generated_object<
            Lambda, BOOST_PP_ENUM_PARAMS(n, A)
        >
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return how_t()(boost::type<Result>(), BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif