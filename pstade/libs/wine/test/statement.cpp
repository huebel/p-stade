#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/statement.hpp>


#include <pstade/instance.hpp>


PSTADE_INSTANCE(int, x, value)

PSTADE_STATEMENT(Update,
	pstade_instance_of_x() = 3;
	pstade_instance_of_x() += 1;
)


void test()
{
    BOOST_CHECK(x == 4);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
