#ifndef BOOST_EGG_BLL_PROTECT_HPP
#define BOOST_EGG_BLL_PROTECT_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lambda/core.hpp> // protect
#include <boost/egg/by_cref.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/overloaded.hpp>
#include <boost/egg/bll/result_of.hpp> // inclusion guaranteed


namespace boost { namespace egg {


    namespace bll_protect_detail {


        struct little
        {
            BOOST_EGG_OVERLOADED_PREAMBLE()

            template<class Me, class T>
            struct apply
            {
                typedef T &type;
            };

            template<class Me, class Arg>
            struct apply<Me, lambda::lambda_functor<Arg> const>
            {
                typedef
                    lambda::lambda_functor<
                        lambda::lambda_functor_base<
                            lambda::protect_action,
                            tuples::tuple< lambda::lambda_functor<Arg> >
                        >
                    >
                type;
            };

            template<class Re, class T>
            Re call(BOOST_EGG_OVERLOADED(Re) T &t) const
            {
                return t;
            }

            template<class Re, class Arg>
            Re call(BOOST_EGG_OVERLOADED(Re) lambda::lambda_functor<Arg> const &lam) const
            {
                return
                    lambda::lambda_functor_base<
                        lambda::protect_action,
                        tuples::tuple< lambda::lambda_functor<Arg> >
                    >(tuples::tuple< lambda::lambda_functor<Arg> >(lam));
            }
        };


    } // namespace bll_protect_detail


    typedef function<bll_protect_detail::little, by_cref> T_bll_protect;
    BOOST_EGG_CONST((T_bll_protect), bll_protect) = {{}};


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
