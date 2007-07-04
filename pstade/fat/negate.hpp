#ifndef PSTADE_FAT_NEGATE_HPP
#define PSTADE_FAT_NEGATE_HPP
#include "./detail/prefix.hpp"


// PStade.Fat
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/remove_const.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/object.hpp>


namespace pstade { namespace fat {


    namespace negate_detail {


        struct baby
        {
            template<class Myself, class X>
            struct apply :
                boost::remove_const<X>
            { };

            template<class Result, class X>
            Result call(X& x) const
            {
                return -x;
            }
        };


    } // negate_detail


    typedef egg::function<negate_detail::baby> op_negate;
    PSTADE_ADL_BARRIER(negate) { // for 'std'
        PSTADE_EGG_OBJECT((op_negate), negate) = { {} };
    }


} } // namespace pstade::fat


#endif
