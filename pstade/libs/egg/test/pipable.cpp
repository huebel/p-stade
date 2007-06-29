#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/pipable.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/object.hpp>
#include <boost/mpl/placeholders.hpp>
#include <pstade/unparenthesize.hpp>
#include <boost/preprocessor/cat.hpp>


    #define PSTADE_EGG_PIPABLE(O, F) \
        namespace BOOST_PP_CAT(pstade_egg_pipable_workarea_of_, O) { \
            using namespace boost::mpl::placeholders; \
            typedef pstade::egg::function< pstade::egg::baby::pipable_result<PSTADE_UNPARENTHESIZE(F)> > pipe; \
        } \
        PSTADE_EGG_OBJECT((BOOST_PP_CAT(pstade_egg_pipable_workarea_of_, O)::pipe), O) = { { } }; \
    /**/



struct my_fun_t
{
    typedef int result_type;

    int operator()(int x) const
    {
        return x + 1;
    }
};

PSTADE_EGG_PIPABLE(my_fun, (my_fun_t))


struct your_fun_t
{
    typedef int result_type;

    int operator()(std::string str, int x, int y) const
    {
        return x + y;
    }
};

PSTADE_EGG_PIPABLE(your_fun, (your_fun_t))


void pstade_minimal_test()
{
    BOOST_CHECK( (3|my_fun) == 4 );
    BOOST_CHECK( (3|my_fun()) == 4 );
    BOOST_CHECK( ("hello"|your_fun(1, 2)) == 3 );
}