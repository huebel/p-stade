#ifndef PSTADE_OVEN_SCANNED_HPP
#define PSTADE_OVEN_SCANNED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/optional/optional.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./detail/scan_iterator.hpp"
#include "./dropped.hpp"
#include "./front.hpp"
#include "./iter_range.hpp"
#include "./jointed.hpp"
#include "./range_iterator.hpp"
#include "./shared_single.hpp"


namespace pstade { namespace oven {


namespace scanned_detail {


    template< class Range, class State, class BinaryFun >
    struct baby
    {
        typedef
            detail::scan_iterator<
                typename range_iterator<Range>::type,
                typename pass_by_value<State>::type,
                typename pass_by_value<BinaryFun>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, State& init, BinaryFun& fun) const
        {
            return result_type(
                iter_t(boost::begin(rng), init, fun),
                iter_t(boost::end(rng),   init, fun)
            );
        }
    };


} // namespace scanned_detail


struct op_make_scanned :
    callable<op_make_scanned>
{
    template< class Myself, class Range, class State, class BinaryFun = void >
    struct apply :
        result_of<
            op_make_jointed(
                typename result_of<op_shared_single(State const *)>::type,
                typename scanned_detail::baby<Range, State, BinaryFun>::result_type
            )
        >
    { };

    template< class Result, class Range, class State, class BinaryFun >
    Result call(Range& rng, State& init, BinaryFun& fun) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        // Prefer const-qualified 'State';
        // It's common that 'rng' is constant but 'init' isn't 'const'.
        // As 'scan_iterator' is constant, 'make_jointed' won't work in such case.
        return make_jointed(
            shared_single(new State const(init)),
            scanned_detail::baby<Range, State, BinaryFun>()(rng, init, fun)
        );
    }

    template< class Myself, class Range, class BinaryFun >
    struct apply<Myself, Range, BinaryFun> :
        result_of<
            op_make_scanned(
                typename result_of<op_make_dropped(Range&, int)>::type,
                typename result_of<op_value_front(Range&)>::type,
                BinaryFun&
            )
        >
    { };

    template< class Result, class Range, class BinaryFun >
    Result call(Range& rng, BinaryFun& fun) const
    {
        BOOST_ASSERT(!boost::empty(rng));
        return (*this)(make_dropped(rng, 1), value_front(rng), fun);
    }
};


PSTADE_CONSTANT(make_scanned, (op_make_scanned))
PSTADE_PIPABLE(scanned, (op_make_scanned))


} } // namespace pstade::oven


#endif