#ifndef PSTADE_OVEN_ZIP_WITH_RANGE_HPP
#define PSTADE_OVEN_ZIP_WITH_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pass_by.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./range_base.hpp"
#include "./transform_range.hpp"
#include "./zip_range.hpp"


namespace pstade { namespace oven {


namespace zip_with_range_detail {


    template<
        class RangeTuple,
        class UnaryFun,
        class Reference,
        class Value
    >
    struct super_
    {
        typedef transform_range<
            zip_range<RangeTuple> const,
            UnaryFun,
            Reference,
            Value
        > type;
    };


} // namespace zip_with_range_detail


template<
    class RangeTuple,
    class UnaryFun,
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct zip_with_range :
    zip_with_range_detail::super_<RangeTuple, UnaryFun, Reference, Value>::type,
    private as_lightweight_proxy< zip_with_range<RangeTuple, UnaryFun, Reference, Value> >
{
    typedef RangeTuple range_tuple_type;

private:
    typedef typename zip_with_range_detail::super_<RangeTuple, UnaryFun, Reference, Value>::type super_t;
    typedef typename range_base<super_t>::type base_t;

public:
    zip_with_range(RangeTuple const& tup, UnaryFun const& fun) :
        super_t(base_t(tup), fun)
    { }
};


namespace zip_with_range_detail {


    struct baby_make
    {
        template< class Myself, class RangeTuple, class UnaryFun >
        struct apply
        {
            typedef typename pass_by_value<RangeTuple>::type tup_t;
            typedef typename pass_by_value<UnaryFun>::type fun_t;
            typedef zip_with_range<tup_t, fun_t> const type;
        };

        template< class Result, class RangeTuple, class UnaryFun >
        Result call(RangeTuple const& tup, UnaryFun& fun)
        {
            return Result(tup, fun);
        }
    };


} // namespace zip_with_range_detail


PSTADE_EGG_FUNCTION(make_zip_with_range, zip_with_range_detail::baby_make)
PSTADE_EGG_PIPABLE(zipped_with, zip_with_range_detail::baby_make)


} } // namespace pstade::oven


#endif
