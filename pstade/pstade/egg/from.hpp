#ifndef PSTADE_EGG_FROM_HPP
#define PSTADE_EGG_FROM_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/none.hpp>
#include <boost/optional/optional.hpp> // inclusion guaranteed
#include <pstade/apple/boost/any_fwd.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/poly_fwd.hpp>
#include "./by_cref.hpp"
#include "./by_perfect.hpp"
#include "./implicit.hpp"


namespace pstade { namespace egg {


    // from_any
    //

    template<class X>
    struct X_from_any_to;

    template<class T>
    struct X_from_any_to< boost::optional<T &> >
    {
        typedef boost::optional<T &> result_type;

        template<class Any>
        result_type operator()(Any const &a) const
        {
            if (a.template contains<T>())
                return a.template content<T>();
            else
                return boost::none;
        }
    };

    typedef implicit<X_from_any_to<mpl_1>, by_cref>::type T_from_any;
    PSTADE_POD_CONSTANT((T_from_any), from_any) = PSTADE_EGG_IMPLICIT();


    // from_boost_any
    //

    template<class X>
    struct X_from_boost_any_to;

    template<class T>
    struct X_from_boost_any_to< boost::optional<T &> >
    {
        typedef boost::optional<T &> result_type;

        result_type operator()(boost::any &a) const
        {
            if (T *p = boost::any_cast<T>(&a))
                return *p;
            else
                return boost::none;
        }

        result_type operator()(boost::any const &a) const
        {
            if (T *p = boost::any_cast<T>(&a))
                return *p;
            else
                return boost::none;
        }
    };

    typedef implicit<X_from_boost_any_to<mpl_1>, by_perfect>::type T_from_boost_any;
    PSTADE_POD_CONSTANT((T_from_boost_any), from_boost_any) = PSTADE_EGG_IMPLICIT();


    // from_poly
    //

    template<class X>
    struct X_from_poly_to;

    template<class T>
    struct X_from_poly_to< boost::optional<T &> >
    {
        typedef boost::optional<T &> result_type;

        template<class O>
        result_type operator()(pstade::poly<O> &p) const
        {
            if (p.template contains<T>())
                return p.template content<T>();
            else
                return boost::none;
        }

        template<class O>
        result_type operator()(pstade::poly<O> const &p) const
        {
            if (p.template contains<T>())
                return p.template content<T>();
            else
                return boost::none;
        }
    };

    typedef implicit<X_from_poly_to<mpl_1>, by_perfect>::type T_from_poly;
    PSTADE_POD_CONSTANT((T_from_poly), from_poly) = PSTADE_EGG_IMPLICIT();


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
