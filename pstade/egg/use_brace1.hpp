#ifndef PSTADE_EGG_USE_BRACE1_HPP
#define PSTADE_EGG_USE_BRACE1_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/use_brace.hpp"


namespace pstade { namespace egg {


    #define  PSTADE_EGG_USE_BRACE_N 1
    #include PSTADE_EGG_USE_BRACE()


} } // namespace pstade::egg


#endif