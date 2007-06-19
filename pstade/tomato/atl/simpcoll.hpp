#ifndef PSTADE_TOMATO_ATL_SIMPCOLL_HPP
#define PSTADE_TOMATO_ATL_SIMPCOLL_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include "./config.hpp" // ATL_VER


#if !(PSTADE_TOMATO_ATL_VER < 0x0700)
    #include <atlsimpcoll.h>
#else
    #include <atlbase.h> // CSimpleArray/ValArray
#endif


#endif
