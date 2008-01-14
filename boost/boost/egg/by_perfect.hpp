#ifndef BOOST_EGG_BY_PERFECT_HPP
#define BOOST_EGG_BY_PERFECT_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/egg/pstade/preprocessor.hpp> // PSTADE_PP_SEQ_RANGE
#include "./config.hpp" // BOOST_EGG_MAX_ARITY
#include "./function_fwd.hpp" // by_perfect
#include "./perfect_strategy.hpp"


#define  BOOST_EGG_PERFECT_STRATEGY_PARAMS (pstade::egg::by_perfect, PSTADE_PP_SEQ_RANGE(0, BOOST_PP_INC(BOOST_EGG_MAX_ARITY)))
#include BOOST_EGG_PERFECT_STRATEGY()


#endif
