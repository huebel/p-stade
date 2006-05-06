#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.P_Stade;
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>
#include "./now.hpp"

void test()
{
	BOOST_CHECK(x_() == 16);
	BOOST_CHECK(y_() == 15);
	
	std::cout << x_() << ',' << y_() << std::endl;
	std::cout << x << ',' << y << std::endl;
}

int test_main(int, char*[])
{
    ::test();
    return 0;
}
