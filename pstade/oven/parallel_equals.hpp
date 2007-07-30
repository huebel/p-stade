#ifndef PSTADE_OVEN_PARALLEL_EQUALS_HPP
#define PSTADE_OVEN_PARALLEL_EQUALS_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/empty.hpp>
#include <boost/ref.hpp>
#include <boost/thread/thread.hpp>
#include <pstade/egg/equal_to.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/make_function.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./equals.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./split_at.hpp"


namespace pstade { namespace oven {


namespace parallel_equals_detail {


    template< class IterRange1, class IterRange2, class Predicate >
    struct aux
    {
    private:
        typedef typename range_difference<IterRange1>::type diff_t;

    public:
        void operator()()
        {
            typename result_of<op_make_split_at(IterRange1&, diff_t&)>::type xs_ys1 = make_split_at(m_rng1, m_grain);

            if (boost::empty(xs_ys1.second)) {
                m_equal = equals(xs_ys1.first, m_rng2);
            }
            else {
                typename result_of<op_make_split_at(IterRange2&, diff_t&)>::type xs_ys2 = make_split_at(m_rng2, m_grain);

                if (boost::empty(xs_ys2.second)) {
                    m_equal = false;
                }
                else {
                    aux auxR(m_grain, xs_ys1.second, xs_ys2.second, m_pred);
                    boost::thread thrd(boost::ref(auxR));
                    m_equal = equals(xs_ys1.first, xs_ys2.first);
                    thrd.join();
                    m_equal = m_equal && auxR.equal();
                }
            }
        }

        template< class Range1, class Range2 >
        aux(diff_t grain, Range1& rng1, Range2& rng2, Predicate pred) :
            m_grain(grain), m_rng1(rng1), m_rng2(rng2), m_pred(pred), m_equal(false)
        { }

        bool equal() const
        {
            return m_equal;
        }

    private:
        diff_t m_grain;
        IterRange1 m_rng1;
        IterRange2 m_rng2;
        Predicate m_pred;
        bool m_equal;
    };


    struct baby
    {
        template< class Myself, class Difference, class Range1, class Range2, class Predicate = egg::op_equal_to const >
        struct apply
        {
            typedef bool type;
        };

        template< class Result, class Difference, class Range1, class Range2, class Predicate >
        Result call(Difference grain, Range1& rng1, Range2& rng2, Predicate pred) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range1>));
            PSTADE_CONCEPT_ASSERT((Forward<Range2>));
            BOOST_ASSERT(grain > 0);

            aux<typename iter_range_of<Range1>::type, typename iter_range_of<Range2>::type, Predicate> auxRoot(grain, rng1, rng2, pred);
            auxRoot();
            return auxRoot.equal();
        }

        template< class Result, class Difference, class Range1, class Range2 >
        Result call(Difference grain, Range1& rng1, Range2& rng2) const
        {
            return egg::make_function(*this)(grain, rng1, rng2, egg::equal_to);
        }
    };


} // namespace parallel_equals_detail


typedef egg::function<parallel_equals_detail::baby> op_parallel_equals;
PSTADE_POD_CONSTANT((op_parallel_equals), parallel_equals) = {{}};


} } // namespace pstade::oven


#endif
