#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>

#include <pstade/ambi.hpp>
#include <pstade/result_of.hpp>
#include <cstring>

using namespace pstade;

void test()
{
    pstade::result_of<
        T_ambi1(int (*)(char const *, char const *))
    >::type compare = ambi1(&std::strcmp);

    BOOST_CHECK( compare("abcd", "abce") < 0 );
    BOOST_CHECK( ("abcd"|compare("abce") ) < 0 );
}


int test_main(int, char *[])
{
    ::test();
    return 0; 
} 
