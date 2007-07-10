#ifndef PSTADE_OVEN_ADJACENT_TRANSFORMED_HPP
#define PSTADE_OVEN_ADJACENT_TRANSFORMED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// The Adaptor version of 'std::adjacent_difference'.


// Question:
//
// See "../../libs/oven/example/adjacent_difference.cpp".
// Should this contain the first value of base range?
// This is symmetrical to 'scanned', which requires
// the first value to be passed. So, it's intuitive
// not to contain the first value of base range, IMO.


#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/range/empty.hpp>
#include <boost/type.hpp>
#include <pstade/egg/tuple_pack.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/result_of.hpp>
#include <pstade/use_default.hpp>
#include "./concepts.hpp"
#include "./detail/adjacent_transform_iterator.hpp"
#include "./detail/baby_to_adaptor.hpp"
#include "./detail/begin_end_tag.hpp"
#include "./dropped.hpp"
#include "./popped.hpp"
#include "./range_iterator.hpp"
#include "./range_traversal.hpp"
#include "./zipped_with.hpp"


namespace pstade { namespace oven {


namespace adjacent_transformed_detail {


    template< class Range, class BinaryFun, class Reference, class Value >
    struct make_single_pass
    {
        typedef typename
            range_iterator<Range>::type
        base_iter_t;

        typedef typename
            pass_by_value<BinaryFun>::type
        fun_t;

        typedef typename
            boost::iterator_value<base_iter_t>::type
        base_value_t;

        typedef typename
            iterator_read<base_iter_t>::type
        read_t;

        typedef typename
            eval_if_use_default<
                Reference,
                result_of<
                    fun_t const(base_value_t const&, read_t)
                >
            >::type
        ref_t;

        typedef typename
            eval_if_use_default<
                Value,
                remove_cvr<ref_t>
            >::type
        val_t;

        typedef
            detail::adjacent_transform_iterator<
                base_iter_t, fun_t, val_t, ref_t
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };


    template< class Range, class BinaryFun, class Reference, class Value >
    struct make_multi_pass :
        result_of<
            xp_make_zipped_with<Reference, Value>(
                typename result_of<
                    egg::op_tuple_pack(
                        typename result_of<op_make_popped(Range&)>::type,
                        typename result_of<op_make_dropped(Range&, int)>::type
                    )
                >::type,
                BinaryFun&
            )
        >
    { };


} // namespace adjacent_transformed_detail


template<
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct tp_make_adjacent_transformed
{
    struct baby
    {
        template< class Myself, class Range, class BinaryFun >
        struct apply :
            boost::mpl::eval_if<
                is_convertible<typename range_traversal<Range>::type, boost::forward_traversal_tag>,
                adjacent_transformed_detail::make_multi_pass< Range, BinaryFun, Reference, Value>,
                adjacent_transformed_detail::make_single_pass<Range, BinaryFun, Reference, Value>
            >
        { };

        template< class Result, class Range, class BinaryFun >
        Result call(Range& rng, BinaryFun& fun) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            BOOST_ASSERT(!boost::empty(rng));

            // gcc3.4 needs "type2type" for 'Result'; see also <pstade/const_overloaded.hpp>.
            return aux(boost::type<Result>(), rng, fun, typename range_traversal<Range>::type());
        }

        template< class Result, class Range, class BinaryFun >
        Result aux(boost::type<Result>, Range& rng, BinaryFun& fun, boost::forward_traversal_tag) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));

            return xp_make_zipped_with<Reference, Value>()(
                egg::tuple_pack(make_popped(rng), make_dropped(rng, 1)), fun
            );
        }

        template< class Result, class Range, class BinaryFun >
        Result aux(boost::type<Result>, Range& rng, BinaryFun& fun, boost::single_pass_traversal_tag) const
        {
            typedef typename Result::iterator iter_t;
            return Result(
                iter_t(boost::begin(rng), fun, detail::begin_tag()), 
                iter_t(boost::end(rng),   fun, detail::end_tag())
            );
        }
    };

    typedef egg::function<baby> type;
};



template<
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct xp_make_adjacent_transformed :
    tp_make_adjacent_transformed<Reference, Value>::type
{ };


PSTADE_OVEN_BABY_TO_ADAPTOR(adjacent_transformed, (tp_make_adjacent_transformed<>::baby))


} } // namespace pstade::oven


#endif
