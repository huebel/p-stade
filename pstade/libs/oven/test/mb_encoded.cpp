#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if defined(_MSC_VER)
#include <pstade/oven/mb_encoded.hpp>
#endif
#include <boost/test/minimal.hpp>
#include "./detail/v1_tests.hpp"


#include <string>
#include <boost/range.hpp>
#include <pstade/locale_saver.hpp>
#include "./detail/v1_core.hpp"


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

#if defined(BOOST_MSVC)
    {
        pstade::locale_saver loc("japanese");
        std::string mb("aあbいcうえde");
        std::wstring wc(L"aあbいcうえde");
        BOOST_CHECK(!oven::equals(mb, wc) );
        BOOST_CHECK( oven::equals(wc|mb_encoded, mb) );
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
