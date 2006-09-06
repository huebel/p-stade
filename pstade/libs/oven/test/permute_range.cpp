#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/permute_range.hpp>


#include <string>
#include <pstade/oven/functions.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        std::string src("0123456789");
        std::string ans("8623");
        int ind[] = { 8, 6, 2, 3 };

        BOOST_CHECK( oven::equals( src|permuted(ind), ans ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
