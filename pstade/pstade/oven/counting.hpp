#ifndef PSTADE_OVEN_COUNTING_HPP
#define PSTADE_OVEN_COUNTING_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// '__w64 int'(msvc) and 'ptrdiff_t'(gcc) behavior seems undefined.
// Through metafunctions, they are occasionally turned into 'int'.


#include <limits> // numeric_limits
#include <boost/assert.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/egg/copy.hpp>
#include <pstade/egg/envelope.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/unused.hpp>
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace counting_detail {


    namespace here = counting_detail;


    template< class Incrementable1, class Incrementable2 > inline
    bool is_valid(Incrementable1 i, Incrementable2 j, boost::single_pass_traversal_tag)
    {
        unused(i, j);
        return true;
    }

    template< class Incrementable1, class Incrementable2 > inline
    bool is_valid(Incrementable1 i, Incrementable2 j, boost::random_access_traversal_tag)
    {
        return egg::copy<Incrementable2>(i) <= j;
    }


    template< class Traversal, class Difference, class Incrementable1, class Incrementable2 >
    struct simple_base
    {
        // Prefer 'Incrementable2'; [0:int, size():uint) often happens.
        typedef typename
            pass_by_value<Incrementable2>::type
        inc_t;

        typedef
            boost::counting_iterator<inc_t, Traversal, Difference>
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Incrementable1& i, Incrementable2& j) const
        {
            BOOST_ASSERT(here::is_valid(i, j, typename boost::iterator_traversal<iter_t>::type()));
            return result_type(iter_t(egg::copy<inc_t>(i)), iter_t(j));
        }
    };


    struct max_count_tag { };
    struct min_count_tag { };


    template< class Traversal, class Difference >
    struct baby
    {
        template< class Incrementable1, class Incrementable2 >
        struct apply_aux
        {
            typedef typename
                simple_base<Traversal, Difference, Incrementable1, Incrementable2>::result_type
            type;
        };

        template< class Result, class Incrementable1, class Incrementable2 >
        Result call_aux(Incrementable1 i, Incrementable2 j, egg::envelope<Result>) const
        {
            return
                simple_base<Traversal, Difference, Incrementable1, Incrementable2>()(i, j);
        }

        template< class Incrementable >
        struct apply_aux<Incrementable, max_count_tag>
        {
            typedef typename
                simple_base<Traversal, Difference, Incrementable, Incrementable const>::result_type
            type;
        };

        template< class Result, class Incrementable >
        Result call_aux(Incrementable i, max_count_tag, egg::envelope<Result>) const
        {
            return
                simple_base<Traversal, Difference, Incrementable, Incrementable const>()(i, (std::numeric_limits<Incrementable>::max)());
        }

        template< class Incrementable >
        struct apply_aux<min_count_tag, Incrementable>
        {
            typedef typename
                simple_base<Traversal, Difference, Incrementable const, Incrementable>::result_type
            type;
        };

        template< class Result, class Incrementable >
        Result call_aux(min_count_tag, Incrementable j, egg::envelope<Result>) const
        {
            return
                simple_base<Traversal, Difference, Incrementable const, Incrementable>()((std::numeric_limits<Incrementable>::min)(), j);
        }

        template< class Myself, class Incrementable1, class Incrementable2 >
        struct apply :
            apply_aux<
                typename pass_by_value<Incrementable1>::type,
                typename pass_by_value<Incrementable2>::type
            >
        { };

        template< class Result, class Incrementable1, class Incrementable2 >
        Result call(Incrementable1& i, Incrementable2& j) const
        {
            // Use type2type for gcc-3.4; see <pstade/const_overloaded.hpp>.
            return call_aux(i, j, egg::envelope<Result>());
        }
    };


} // namespace counting_detail


template<
    class Traversal  = boost::use_default,
    class Difference = boost::use_default
>
struct tp_counting
{
    typedef egg::function< counting_detail::baby<Traversal, Difference> > type;
};


template<
    class Traversal  = boost::use_default,
    class Difference = boost::use_default
>
struct xp_counting :
    tp_counting<Traversal, Difference>::type
{ };


typedef tp_counting<>::type op_counting;
PSTADE_POD_CONSTANT((op_counting), counting) = {{}};


PSTADE_POD_CONSTANT((counting_detail::max_count_tag), max_count) = {};
PSTADE_POD_CONSTANT((counting_detail::min_count_tag), min_count) = {};


} } // namespace pstade::oven


#endif