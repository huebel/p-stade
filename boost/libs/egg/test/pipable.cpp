

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/pipable.hpp>
#include "./egg_test.hpp"


#include <boost/egg/const.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/egg/detail/unparen.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include "./large_arity_id0.hpp"

#include <string>


    #define EGG_pipable_def(O, F) \
        namespace BOOST_PP_CAT(pstade_egg_pipable_workarea_of_, O) { \
            using namespace boost::mpl::placeholders; \
            typedef boost::egg::result_of_pipable<BOOST_EGG_UNPAREN(F)>::type pipe; \
        } \
        BOOST_EGG_CONST((BOOST_PP_CAT(pstade_egg_pipable_workarea_of_, O)::pipe), O) = BOOST_EGG_PIPABLE({}); \
    /**/



struct my_fun_t
{
    typedef int result_type;

    int operator()(int x) const
    {
        return x + 1;
    }
};

EGG_pipable_def(my_fun, (my_fun_t))


struct your_fun_t
{
    typedef int result_type;

    int operator()(std::string str, int x, int y) const
    {
        return x + y;
    }
};

EGG_pipable_def(your_fun, (your_fun_t))


struct my_plus_t
{
    typedef int result_type;

    int operator()(int x, int y) const
    {
        return x + y;
    }
};

EGG_pipable_def(my_plus, (my_plus_t))


struct my_mult_t
{
    typedef int result_type;

    int operator()(int x, int y) const
    {
        return x * y;
    }
};

EGG_pipable_def(my_mult, (my_mult_t))


struct my_append_t
{
    typedef std::string result_type;

    std::string operator()(std::string s, char ch) const
    {
        s.push_back(ch);
        return s;
    }
};

EGG_pipable_def(my_append, (my_append_t))


using namespace boost::egg;

result_of_pipable<T_large_arity_id0, by_cref>::type const lar = BOOST_EGG_PIPABLE_L {} BOOST_EGG_PIPABLE_R;


void egg_test()
{
    {
        BOOST_CHECK( (3|my_fun) == 4 );
        BOOST_CHECK( (3|my_fun()) == 4 );
        BOOST_CHECK( ("hello"|your_fun(1, 2)) == 3 );
        BOOST_CHECK( (3|my_plus(4)|my_mult(5)) == (3+4)*5 );
        BOOST_CHECK( (std::string("my_")|my_append('a')|my_append('b')) == "my_ab" );
        {
            using namespace large_arity_helpers;
            BOOST_CHECK( &(i0|lar(i1,i2,i3,i4,i5,i6,i7,ci8,ci9)) == &i0 );        
        }
    }
    {
        BOOST_CHECK( (my_fun |= 3) == 4 );
        BOOST_CHECK( (my_fun() |= 3) == 4 );
        BOOST_CHECK( (your_fun(1, 2) |= "hello") == 3 );
        BOOST_CHECK( (my_mult(5) |= my_plus(4) |= 3) == (3+4)*5 );
        BOOST_CHECK( (my_append('b') |= my_append('a') |= std::string("my_")) == "my_ab" );

        {
            using namespace large_arity_helpers;
            BOOST_CHECK( &(lar(i1,i2,i3,i4,i5,i6,i7,ci8,ci9) |= i0) == &i0 );        
        }
    }
}
