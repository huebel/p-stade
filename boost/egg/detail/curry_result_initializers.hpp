#ifndef BOOST_EGG_DETAIL_CURRY_RESULT_INITIALIZERS_HPP
#define BOOST_EGG_DETAIL_CURRY_RESULT_INITIALIZERS_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/preprocessor/cat3.hpp>
#include <boost/egg/detail/bind_left1.hpp>
#include <boost/egg/detail/bind_leftx.hpp>


#define BOOST_EGG_CURRY_L(N) BOOST_EGG_PP_CAT3(BOOST_EGG_CURRY, N, _L)
#define BOOST_EGG_CURRY_R(N) BOOST_EGG_PP_CAT3(BOOST_EGG_CURRY, N, _R)

// BOOST_EGG_BIND_LEFT1_L BOOST_EGG_BIND_LEFTX_INIT , Base BOOST_EGG_BIND_LEFT1_R
#define BOOST_EGG_CURRY_left  BOOST_EGG_BIND_LEFT1_L BOOST_EGG_BIND_LEFTX_INIT ,
#define BOOST_EGG_CURRY_right BOOST_EGG_BIND_LEFT1_R

#define BOOST_EGG_CURRY2_L BOOST_EGG_CURRY_left
#define BOOST_EGG_CURRY2_R BOOST_EGG_CURRY_right

#define BOOST_EGG_CURRY3_L BOOST_EGG_CURRY_left BOOST_EGG_CURRY2_L
#define BOOST_EGG_CURRY3_R BOOST_EGG_CURRY2_R BOOST_EGG_CURRY_right

#define BOOST_EGG_CURRY4_L BOOST_EGG_CURRY_left BOOST_EGG_CURRY3_L
#define BOOST_EGG_CURRY4_R BOOST_EGG_CURRY3_R BOOST_EGG_CURRY_right

#define BOOST_EGG_CURRY5_L BOOST_EGG_CURRY_left BOOST_EGG_CURRY4_L
#define BOOST_EGG_CURRY5_R BOOST_EGG_CURRY4_R BOOST_EGG_CURRY_right

#define BOOST_EGG_CURRY6_L BOOST_EGG_CURRY_left BOOST_EGG_CURRY5_L
#define BOOST_EGG_CURRY6_R BOOST_EGG_CURRY5_R BOOST_EGG_CURRY_right

#define BOOST_EGG_CURRY7_L BOOST_EGG_CURRY_left BOOST_EGG_CURRY6_L
#define BOOST_EGG_CURRY7_R BOOST_EGG_CURRY6_R BOOST_EGG_CURRY_right

#define BOOST_EGG_CURRY8_L BOOST_EGG_CURRY_left BOOST_EGG_CURRY7_L
#define BOOST_EGG_CURRY8_R BOOST_EGG_CURRY7_R BOOST_EGG_CURRY_right

#define BOOST_EGG_CURRY9_L BOOST_EGG_CURRY_left BOOST_EGG_CURRY8_L
#define BOOST_EGG_CURRY9_R BOOST_EGG_CURRY8_R BOOST_EGG_CURRY_right

#define BOOST_EGG_CURRY10_L BOOST_EGG_CURRY_left BOOST_EGG_CURRY9_L
#define BOOST_EGG_CURRY10_R BOOST_EGG_CURRY9_R BOOST_EGG_CURRY_right


// #define BOOST_EGG_CURRY(N) BOOST_PP_CAT(BOOST_EGG_CURRY, N)
#define BOOST_EGG_CURRY2(F) BOOST_EGG_CURRY2_L F BOOST_EGG_CURRY2_R
#define BOOST_EGG_CURRY3(F) BOOST_EGG_CURRY3_L F BOOST_EGG_CURRY3_R
#define BOOST_EGG_CURRY4(F) BOOST_EGG_CURRY4_L F BOOST_EGG_CURRY4_R
#define BOOST_EGG_CURRY5(F) BOOST_EGG_CURRY5_L F BOOST_EGG_CURRY5_R
#define BOOST_EGG_CURRY6(F) BOOST_EGG_CURRY6_L F BOOST_EGG_CURRY6_R
#define BOOST_EGG_CURRY7(F) BOOST_EGG_CURRY7_L F BOOST_EGG_CURRY7_R
#define BOOST_EGG_CURRY8(F) BOOST_EGG_CURRY8_L F BOOST_EGG_CURRY8_R
#define BOOST_EGG_CURRY9(F) BOOST_EGG_CURRY9_L F BOOST_EGG_CURRY9_R
#define BOOST_EGG_CURRY10(F) BOOST_EGG_CURRY10_L F BOOST_EGG_CURRY10_R


#endif
