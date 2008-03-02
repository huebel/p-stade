

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/ptr_new.hpp>
#include "./egg_test.hpp"


#include "./check_is_result_of.hpp"
#include <boost/mpl/apply.hpp>


#include "./using_egg.hpp"


struct udt
{
    udt(int i, int j)
        : m_i(i), m_j(j)
    { }

    int m_i, m_j;
};


CHECK_IS_RESULT_OF(int *, X_ptr_new<int *>())
CHECK_IS_RESULT_OF(int *, X_ptr_new<int *>(int))


CHECK_IS_RESULT_OF(udt *, X_ptr_new<udt *>(int,int))
CHECK_IS_RESULT_OF(udt const*, X_ptr_new<udt const *>(int,int))


void egg_test()
{
    {
        udt *p = X_ptr_new<udt *>()(1,2);
        BOOST_CHECK(p->m_i == 1);
        BOOST_CHECK(p->m_j == 2);
        delete p;
    }
    {
        typedef boost::mpl::apply1<X_ptr_new<boost::mpl::_1>, int *>::type aaa_t;
    }
}
