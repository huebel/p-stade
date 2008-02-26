#ifndef BOOST_EGG_DETAIL_CONST_OVERLOADED_HPP
#define BOOST_EGG_DETAIL_CONST_OVERLOADED_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// GCC3.4.4 cannot order overloadings of non-const-reference and const-reference
// if it has explicit template arguments.
// So disable the non-const-reference overloading in the case of const-reference.
//
// See: http://tinyurl.com/yhqedd
//
// comp.lang.c++.moderated
// "Forwarding Function Template Resolution and Explicit Template Argument"
//
// After all, GCC overload-resolution is broken with explicit template argument.
// We sooner or later need 'ARRAY_OVERLOADED', too.


#include <boost/egg/detail/boost_workaround.hpp>


// This macro can't always be turned on; especially under VC++.
#if BOOST_WORKAROUND(__GNUC__, == 3) || BOOST_WORKAROUND(__EDG_VERSION__, BOOST_TESTED_AT(306))


    #include <boost/mpl/or.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/type_traits/is_const.hpp>
    #include <boost/egg/preprocessor/enum_params_with.hpp>
    #include <boost/egg/detail/enable_if.hpp> // disable_if_


    #define BOOST_EGG_CONST_OVERLOADED(T) \
        , typename boost::egg::disable_if_< boost::is_const<T> >::type = 0 \
    /**/


    #define BOOST_EGG_CONST_OVERLOADED_PARAMS(N, T) \
        , typename boost::egg::disable_if_< \
            boost::egg::details::exists_const<BOOST_PP_ENUM_PARAMS(N, T)> \
        >::type = 0 \
    /**/



    namespace boost { namespace egg { namespace details {


        template<BOOST_EGG_PP_ENUM_PARAMS_WITH(10, class T, = void)>
        struct exists_const :
            mpl::or_<
                mpl::or_< BOOST_EGG_PP_ENUM_PARAMS_WITH(5, is_const<T, >) >,
                mpl::or_< BOOST_EGG_PP_ENUM_PARAMS_WITH(5, is_const<T, >) >
            >
        { };


    } } } // namespace boost::egg::details


#else


    #define BOOST_EGG_CONST_OVERLOADED(T)
    #define BOOST_EGG_CONST_OVERLOADED_PARAMS(N, T)


#endif


#endif
