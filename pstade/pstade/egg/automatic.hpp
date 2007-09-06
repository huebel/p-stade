#ifndef PSTADE_EGG_AUTOMATIC_HPP
#define PSTADE_EGG_AUTOMATIC_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This couldn't support the reference type as 'To',
// because the behavior of conversion-operator template
// varies from compiler to compiler...
//
// 
// 'x|foo' seems impossible without yet another 'function<>'.
// Use 'x|foo()' instead.


#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp> // inclusion guaranteed
#include "./by_cref.hpp"
#include "./fuse.hpp"
#include "./unfuse.hpp"


namespace pstade { namespace egg {


    namespace automatic_detail {


        template<class Lambda, class ArgTuple>
        struct automator
        {
            ArgTuple m_args;

            template<class To>
            operator To() const
            {
                typedef typename
                    boost::mpl::apply1<Lambda, To>::type
                fun_t;

                return fuse(fun_t())(m_args);
            }
        };


        template<class Lambda>
        struct baby_fused
        {
            template<class Myself, class ArgTuple>
            struct apply
            {
                typedef
                    automator<Lambda, ArgTuple> const
                type;
            };

            template<class Result, class ArgTuple>
            Result call(ArgTuple& args) const
            {
                // 'automator' must *copy* it to 'm_args';
                // 'args' is destructed as soon as this 'call' returns.
                Result r = { args };
                return r;
            }
        };


    } // namespace automatic_detail


    template<class Lambda, class Pass = boost::use_default>
    struct automatic :
        result_of_unfuse<
            function<automatic_detail::baby_fused<Lambda>, by_cref>,
            boost::use_default,
            use_nullary_result,
            Pass
        >
    { };


    #define PSTADE_EGG_AUTOMATIC \
        PSTADE_EGG_UNFUSE_L {{}} PSTADE_EGG_UNFUSE_M PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_UNFUSE_R
    /**/


} } // namespace pstade::egg


#endif