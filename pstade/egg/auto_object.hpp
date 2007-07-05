#ifndef PSTADE_EGG_AUTO_OBJECT_HPP
#define PSTADE_EGG_AUTO_OBJECT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <boost/preprocessor/facilities/identity.hpp>
#include <pstade/any_movable.hpp>
#include <pstade/pass_by.hpp>
#include "./function.hpp"
#include "./fuse.hpp"
#include "./new.hpp"
#include "./object.hpp"
#include "./unfuse.hpp"


namespace pstade { namespace egg {


    namespace auto_object_detail {


        // 'automatic' doesn't work; 'auto_ptr' is not CopyConstructible.
        // Note also 'operator auto_ptr_ref<X>()' can't be of help, because
        // some implementations require "move sequence" to be in the same scope.
        // After all, we need a conversion operator to return "lvalue".


        template<class ArgTuple>
        struct automator
        {
            explicit automator(ArgTuple const& args) :
                m_args(args)
            { }

            template<class X>
            operator std::auto_ptr<X>& ()
            {
                std::auto_ptr<X> ptr(fuse(xp_new_<X>())(m_args));
                m_any = ptr;
                return m_any.base< std::auto_ptr<X> >();
            }

        private:
            ArgTuple m_args;
            any_movable m_any;

            automator& operator=(automator const&);
        };


        struct baby_fused
        {
            template<class Myself, class ArgTuple>
            struct apply
            {
                typedef
                    automator<typename pass_by_value<ArgTuple>::type>
                type;
            };

            template<class Result, class ArgTuple>
            Result call(ArgTuple& args) const
            {
                return Result(args); 
            }
        };


        typedef function<baby_fused> fused;


    } // namespace auto_object_detail


    typedef
        result_of_unfuse<
            auto_object_detail::fused,
            boost::use_default,
            use_nullary_result
        >::type
    op_auto_object;


    PSTADE_EGG_OBJECT((op_auto_object), auto_object)
        = PSTADE_EGG_UNFUSE_RESULT_INITIALIZER(BOOST_PP_IDENTITY({{}}), BOOST_PP_IDENTITY({}));


} } // namespace pstade::egg


#endif