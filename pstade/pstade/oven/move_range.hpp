#ifndef PSTADE_OVEN_MOVE_RANGE_HPP
#define PSTADE_OVEN_MOVE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Pending...
//


// Note:
//
// Is this range is really needed?
// 'transformed(move)' seems enough?


#include <boost/move.hpp>
#include <boost/mpl/if.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_value.hpp"
#include "./transform_range.hpp"


namespace pstade { namespace oven {


namespace move_range_detail {


    template< class Value >
    struct move_fun
    {
        typedef typename boost::mpl::if_<
            boost::is_movable<Value>,
            Value, Value&
        >::type result_type;

        template< class T >
        result_type operator()(T& x) const
        {
            return boost::move(x);
        }
    };


    template< class LValueRange >
    struct super_
    {
        typedef transform_range<
            LValueRange,
            move_fun<typename range_value<LValueRange>::type>
        > type;
    };


} // namespace move_range_detail


template< class LValueRange >
struct move_range :
    move_range_detail::super_<LValueRange>::type,
    private as_lightweight_proxy< move_range<LValueRange> >
{
    typedef LValueRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(LValueRange, SinglePassRangeConcept);
    typedef typename move_range_detail::super_<LValueRange>::type super_t;
    typedef typename super_t::function_type fun_t;

public:
    explicit move_range(LValueRange& rng) :
        super_t(rng, fun_t())
    { }
};


namespace move_range_detail {


    struct baby_make
    {
        template< class Myself, class LValueRange >
        struct apply
        {
            typedef move_range<LValueRange> const type;
        };

        template< class Result, class LValueRange >
        Result call(LValueRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace move_range_detail


PSTADE_EGG_FUNCTION(make_move_range, move_range_detail::baby_make)
PSTADE_EGG_PIPABLE(moved, move_range_detail::baby_make)


} } // namespace pstade::oven


#endif
