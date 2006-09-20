#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/function_output_iterator.hpp>


#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <boost/range.hpp>
#include <pstade/oven/identity_range.hpp>
#include <pstade/oven/regularize_iterator.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/unused.hpp>
#include <pstade/oven/iterators.hpp>


std::stringstream g_ss;


void to_ss(char ch)
{
    g_ss << ch;
}


void modify(char& ch)
{
    ch = 'x';
}


void test()
{
    using namespace pstade;
    using namespace oven;

    std::string const src("hello,to_function");
    {
        g_ss.str("");
        oven::copy(src, oven::to_function(to_ss));
        BOOST_CHECK( oven::equals(g_ss.str(), src) );
    }
    {
        g_ss.str("");
        oven::copy(src, oven::make_regularize_iterator(oven::to_function(to_ss)));
        BOOST_CHECK( oven::equals(g_ss.str(), src) );
    }
    {
        g_ss.str("");
        oven::copy(src, oven::to_regularized_function(to_ss));
        BOOST_CHECK( oven::equals(g_ss.str(), src) );
    }
    {
        std::vector<char> vec;
        oven::copy(std::string("abc"), oven::to_back_of(vec));
        BOOST_CHECK( oven::equals(std::string("abc"), vec) );
        // identities keeps vec mutable.
        oven::copy(vec|identities, oven::to_function(&::modify));
        BOOST_CHECK( oven::equals(std::string("xxx"), vec) );
    }
    {
        g_ss.str("");
        oven::copy(src, oven::to_stream(g_ss));
        BOOST_CHECK( oven::equals(g_ss.str(), src) );
    }
    {
        g_ss.str("");
        oven::copy(src, oven::to_ostreambuf(g_ss));
        BOOST_CHECK( oven::equals(g_ss.str(), src) );
    }
    {
        g_ss.str("");
        oven::copy(src, oven::to_function(unused));
        BOOST_CHECK( boost::empty(g_ss.str()) );
    }

    {
        std::list<char> seq;
        oven::copy(std::string("abc"), oven::to_front_of(seq));
        oven::copy(std::string("xyz"), oven::to_back_of(seq));
        BOOST_CHECK( oven::equals(std::string("cbaxyz"), seq) );
    }
    {
        std::list<char> seq; seq.push_back('_');
        oven::copy(std::string("abc"), oven::to_sequence(seq, boost::begin(seq)));
        oven::copy(std::string("xyz"), oven::to_sequence(seq, boost::end(seq)));
        BOOST_CHECK( oven::equals(std::string("abc_xyz"), seq) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
