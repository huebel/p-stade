#ifndef PSTADE_OVEN_PARALLEL_SORT_HPP
#define PSTADE_OVEN_PARALLEL_SORT_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // inplace_merge, sort
#include <pstade/egg/function.hpp>
#include <pstade/egg/less.hpp>
#include <pstade/egg/make_function.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/unused.hpp>
#include "./concepts.hpp"
#include "./detail/simple_parallel.hpp"


namespace pstade { namespace oven {


namespace parallel_sort_detail {


    template< class Compare >
    struct algo :
        detail::simple_parallel_algo< algo<Compare> >
    {
        template< class Iterator >
        void before_join(Iterator first, Iterator last) const
        {
            std::sort(first, last, m_comp);
        }

        template< class Iterator >
        void after_join(Iterator first, Iterator last, Iterator firstR, Iterator lastR, algo const& right) const
        {
            unused(firstR, right);
            std::inplace_merge(first, last, lastR, m_comp);
        }

        explicit algo(Compare comp) :
            m_comp(comp)
        { }

    private:
        Compare m_comp;
    };


    struct baby
    {
        template< class Myself, class Difference, class Range, class Compare = egg::op_less const >
        struct apply
        {
            typedef void type;
        };

        template< class Result, class Difference, class Range, class Compare >
        void call(Difference grain, Range& rng, Compare comp) const
        {
            PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));
            detail::simple_parallel(grain, rng, algo<Compare>(comp));
        }

        template< class Result, class Difference, class Range >
        void call(Difference grain, Range& rng) const
        {
            egg::make_function(*this)(grain, rng, egg::less);
        }
    };


} // namespace parallel_sort_detail


typedef egg::function<parallel_sort_detail::baby> op_parallel_sort;
PSTADE_POD_CONSTANT((op_parallel_sort), parallel_sort) = {{}};


} } // namespace pstade::oven


#endif
