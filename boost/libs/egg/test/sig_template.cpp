#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/bll_bindable.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


struct my_bindable
{
#include BOOST_EGG_BLL_BINDABLE()
};


struct my_bindable2
{
#include BOOST_EGG_BLL_BINDABLE()
};


void pstade_minimal_test()
{
    std::string s1, s2("hello");
}
