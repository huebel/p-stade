#ifndef PSTADE_OVEN_AS_C_STR_HPP
#define PSTADE_OVEN_AS_C_STR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <cstring> // strlen
#include <cwchar>  // wcslen
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/constant.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include "./algorithm.hpp" // find
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_value.hpp"
#include "./sub_range_result.hpp"


namespace pstade { namespace oven {


namespace as_c_str_detail {


    inline
    std::size_t length(char const *psz)
    {
        using namespace std;
        return strlen(psz);
    }

    inline
    std::size_t length(wchar_t const *psz)
    {
        using namespace std;
        return wcslen(psz);
    }


    template< class X >
    struct is_cstring :
       boost::mpl::or_<
            boost::is_convertible<X, char const *>,
            boost::is_convertible<X, wchar_t const *>
        >
    { };

    template< class CString >
    struct cstring_to_range
    {
        typedef
            iter_range<typename pass_by_value<CString>::type> const
        type;
    };


    // suppres warning: comparison between signed and unsigned integer
    template< class Range > inline
    typename range_value<Range>::type
    zero()
    {
        return 0;
    }


    template< class Range, class = enabler >
    struct baby
    {
        typedef typename
            sub_range_result<Range>::type
        result;

        result call(Range& rng)
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            return result(boost::begin(rng), find(rng, zero<Range>()));
        }
    };

    template< class CString >
    struct baby<CString, typename enable_if< is_cstring<CString> >::type>
    {
        typedef typename
            cstring_to_range<CString>::type
        result;

        template< class Char >
        result call(Char *psz)
        {
            return result(psz, psz + length(psz));
        }
    };


} // namespace as_c_str_detail


PSTADE_AUXILIARY0(as_c_str, (function< as_c_str_detail::baby<boost::mpl::_> >))


struct op_contains_zero
{
    typedef bool result_type;

    template< class Range >
    bool operator()(Range const& rng) const
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));
        return find(rng, as_c_str_detail::zero<Range>()) != boost::end(rng);
    }
};

PSTADE_CONSTANT(contains_zero, (op_contains_zero))


} } // namespace pstade::oven


#endif
