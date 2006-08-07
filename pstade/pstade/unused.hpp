#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_UNUSED_HPP
#define PSTADE_UNUSED_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/instance.hpp>


#if !defined(PSTADE_UNUSED_MAX_ARITY)
    #define PSTADE_UNUSED_MAX_ARITY 20
#endif


namespace pstade {


struct unused_fun
{
    typedef void result_type;

    // 0ary
    void operator()() const
    { }

    // 1ary
    template< class A0 >
    void operator()(A0 const&) const
    { }

    // 2ary
    template< class A0, class A1 >
    void operator()(A0 const&, A1 const&) const
    { }

    // 3ary -
    #define PSTADE_UNUSED_arg(Z, N, _) BOOST_PP_CAT(A, N) const&

    #define BOOST_PP_ITERATION_PARAMS_1 (3, (3, PSTADE_UNUSED_MAX_ARITY, <pstade/unused.hpp>))
    #include BOOST_PP_ITERATE()

    #undef PSTADE_UNUSED_arg
};


PSTADE_INSTANCE(unused_fun const, unused, value)


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template< BOOST_PP_ENUM_PARAMS(n, class A) >
void operator()( BOOST_PP_ENUM(n, PSTADE_UNUSED_arg, ~) ) const
{ }


#undef n
#endif
