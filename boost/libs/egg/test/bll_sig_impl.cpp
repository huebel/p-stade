

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/bll/sig_impl.hpp>
#include "./egg_test.hpp"


#include BOOST_EGG_SUPPRESS_WARNING_BEGIN()
#include <boost/lambda/core.hpp>
#include <boost/lambda/bind.hpp>
#include BOOST_EGG_SUPPRESS_WARNING_END()


struct T_my_plus
{
    template<class FunCall>
    struct result;

    template<class Fun, class X, class Y>
    struct result<Fun(X &, Y &)>
    {
        typedef X type;
    };

    template<class X, class Y>
    X operator()(X& x, Y& y) const
    {
        return x + y;
    }

    template<class FunArgs>
    struct sig : boost::egg::bll_sig_impl<FunArgs>
    { };
};

T_my_plus const my_plus = {};


void egg_test()
{
    namespace bll = boost::lambda;

    int two = 2;
    BOOST_CHECK(bll::bind(my_plus, 1, bll::_1)(two) == 1+2);
}
