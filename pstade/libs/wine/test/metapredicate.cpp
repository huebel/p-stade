#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/metapredicate.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>


namespace xxx {

PSTADE_METAPREDICATE(heavy, xxx)

}


namespace yyy {

    struct heavy1 :
        private xxx::as_heavy<heavy1>
    { };

    struct heavy2
    { };

}

pstade::oui xxx_is_heavy(yyy::heavy2 *&, pstade::overload<>)
{ return true; }


struct heavy3
{ };

namespace xxx {

    template< >
    struct is_heavy_impl<heavy3> :
        boost::mpl::true_
    { };

}


struct light
{ };


BOOST_MPL_ASSERT(( xxx::is_heavy<yyy::heavy1> ));
BOOST_MPL_ASSERT(( xxx::is_heavy<yyy::heavy2> ));
BOOST_MPL_ASSERT(( xxx::is_heavy<heavy3> ));
BOOST_MPL_ASSERT_NOT(( xxx::is_heavy<light> ));


void test()
{
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
