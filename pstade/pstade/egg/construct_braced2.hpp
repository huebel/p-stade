#ifndef PSTADE_EGG_CONSTRUCT_BRACED2_HPP
#define PSTADE_EGG_CONSTRUCT_BRACED2_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/construct_xxx.hpp"


#define  PSTADE_EGG_CONSTRUCT_BRACED2_RETURN(T, x, Args) \
    T x = { { Args } }; \
    return x; \
/**/
#define  PSTADE_EGG_CONSTRUCT_XXX_PARAMS (construct_braced2, PSTADE_EGG_CONSTRUCT_BRACED2_RETURN)
#include PSTADE_EGG_CONSTRUCT_XXX() 


#include "./detail/suffix.hpp"
#endif
