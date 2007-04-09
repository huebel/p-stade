#ifndef PSTADE_OVEN_STEPS_HPP
#define PSTADE_OVEN_STEPS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Note:
//
// It seems impossible to be Bidirectional;
// how to step backward from the end iterator?


#include <algorithm> // min
#include <boost/iterator/iterator_categories.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./range_difference.hpp"
#include "./successors.hpp"


namespace pstade { namespace oven {


namespace steps_detail {


    template< class Difference >
    struct step
    {
        template< class Iterator >
        Iterator operator()(Iterator const& first, Iterator const& last) const
        {
            return aux(first, last,
                typename boost::iterator_traversal<Iterator>::type()
            );
        }

        template< class Iterator >
        Iterator aux(Iterator first, Iterator const& last,
            boost::random_access_traversal_tag) const
        {
            return first + (std::min)(last - first, m_stride);
        }

        template< class Iterator >
        Iterator aux(Iterator first, Iterator const& last,
            boost::single_pass_traversal_tag) const
        {
            Difference d = m_stride;
            do {
                ++first;
                --d;
            } while (d != 0 && first != last);

            return first;
        }

        explicit step()
        { }

        explicit step(Difference const& stride) :
            m_stride(stride)
        { }

    private:
        Difference m_stride;
    };


    template< class Range, class >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef typename
            boost::result_of<
                op_make_successors(Range&, step<diff_t>)
            >::type
        result_type;

        result_type operator()(Range& rng, diff_t const& stride) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            BOOST_ASSERT(1 <= stride);
            return make_successors(rng, step<diff_t>(stride));
        }
    };


} // namespace steps_detail


PSTADE_FUNCTION(make_steps, (steps_detail::baby<_, _>))
PSTADE_PIPABLE(steps, (op_make_steps))


} } // namespace pstade::oven


#endif
