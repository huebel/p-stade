

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/stateless.hpp>
#include "./egg_test.hpp"


#include <boost/egg/indirect.hpp>
#include <boost/egg/construct.hpp>


#include "./using_egg.hpp"


typedef stateless< X_construct<int, boost::mpl::_1> >::type T_construct_int;
T_construct_int const construct_int = BOOST_EGG_STATELESS();


void egg_test()
{
    int x = construct_int(3);
    BOOST_CHECK(x == 3);
}
