#ifndef PSTADE_SHARED_NEW_HPP
#define PSTADE_SHARED_NEW_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/shared_ptr.hpp>
#include "./ptr_new.hpp"
#include "./register_nullary_result.hpp"


namespace pstade { namespace egg {


    template<class X, class Strategy = boost::use_default>
    struct X_shared_new :
        X_ptr_new<boost::shared_ptr<X>, Strategy>
    { };


} } // namespace pstade::egg


PSTADE_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE(pstade::egg::X_shared_new, (class)(class))


#endif
