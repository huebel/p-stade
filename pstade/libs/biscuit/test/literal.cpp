#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/algorithm/match.hpp>
#include <pstade/biscuit/parser.hpp>


#include <string>


using namespace pstade;
using namespace biscuit;


PSTADE_BISCUIT_LITERAL_SEQ(hello, "hello")
PSTADE_BISCUIT_LITERAL_SEQ(bye, L"bye")

PSTADE_BISCUIT_LITERAL_SET(hello_, "hello")
PSTADE_BISCUIT_LITERAL_SET(bye_, L"bye")


void test()
{
    BOOST_CHECK(( biscuit::match< seq< hello, chseq<'!'> > >(std::string("hello!")) ));
    BOOST_CHECK(( biscuit::match< seq< chseq<'*'>, bye > >(std::wstring(L"*bye")) ));
    BOOST_CHECK((!biscuit::match< seq< hello, chseq<'!'> > >(std::string("heLlo!")) ));
    BOOST_CHECK((!biscuit::match< seq< chseq<'*'>, bye > >(std::wstring(L"*byi")) ));

    BOOST_CHECK(( biscuit::match< seq< hello_, chseq<'!'> > >(std::string("h!")) ));
    BOOST_CHECK(( biscuit::match< seq< chseq<'*'>, bye_ > >(std::wstring(L"*y")) ));
    BOOST_CHECK((!biscuit::match< seq< hello_, chseq<'!'> > >(std::string("p!")) ));
    BOOST_CHECK((!biscuit::match< seq< chseq<'*'>, bye_ > >(std::wstring(L"*k")) ));
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
