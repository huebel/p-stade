#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_LITTLE_FUSE_RESULT_HPP
#define PSTADE_EGG_DETAIL_LITTLE_FUSE_RESULT_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "../fusion/length.hpp"
#include "../get.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Base>
    struct little_fuse_result
    {
        Base m_base;

        Base const &base() const
        {
            return m_base;
        }

        template<class Tuple, class Arity>
        struct apply_aux;

        template<class Me, class Tuple>
        struct apply :
            apply_aux<Tuple, typename fusion_length<Tuple>::type>
        { };

        template<class Re, class Tuple>
        Re call(Tuple &t) const
        {
            return call_aux<Re>(t, typename fusion_length<Tuple>::type());
        }

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/little_fuse_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Tuple>
    struct apply_aux< Tuple, boost::mpl::int_<n> > :
        result_of<
            Base const( PSTADE_PP_ENUM_PARAMS_WITH(n, typename result_of<X_get_c<PSTADE_PP_INT_, >(Tuple &)>::type) )
        >
    { };

    template<class Re, class Tuple>
    Re call_aux(Tuple &t, boost::mpl::int_<n>) const
    {
        return m_base( PSTADE_PP_ENUM_PARAMS_WITH(n, X_get_c<PSTADE_PP_INT_, >()(t)) );
    }


#undef  n
#endif
