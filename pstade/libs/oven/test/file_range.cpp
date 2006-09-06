#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/file_range.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        file_range<> frng("non-exist.file");
        BOOST_CHECK(( boost::empty(frng) ));
        BOOST_CHECK(( !frng.is_open() ));
    }
    {
        std::vector<char> vec;
        oven::copy(file_range<char>("data.txt"), std::back_inserter(vec));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
