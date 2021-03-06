#ifndef PSTADE_EGG_CONSTRUCT_UNFUSED1_HPP
#define PSTADE_EGG_CONSTRUCT_UNFUSED1_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/construct_xxx.hpp"
#include "./unfuse.hpp"


#define  PSTADE_EGG_CONSTRUCT_UNFUSED1_RETURN(T, x, Args) \
    T x = PSTADE_EGG_UNFUSE_L { Args } PSTADE_EGG_UNFUSE_R; \
    return x; \
/**/
#define  PSTADE_EGG_CONSTRUCT_XXX_PARAMS (construct_unfused1, PSTADE_EGG_CONSTRUCT_UNFUSED1_RETURN)
#include PSTADE_EGG_CONSTRUCT_XXX() 


#include "./detail/suffix.hpp"
#endif
