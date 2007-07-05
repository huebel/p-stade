#ifndef PSTADE_EGG_CONSTRUCTOR_HPP
#define PSTADE_EGG_CONSTRUCTOR_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/placeholders.hpp>
#include "./automatic.hpp"
#include "./object.hpp"
#include "./construct.hpp"


namespace pstade { namespace egg {


    typedef
        automatic<
            xp_construct<boost::mpl::_1>
        >::type
    op_constructor;


    PSTADE_EGG_OBJECT((op_constructor), constructor) = PSTADE_EGG_AUTOMATIC_INITIALIZER();


} } // namespace pstade::egg


#endif