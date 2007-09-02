#ifndef PSTADE_KETCHUP_CONFIG_LIMIT_TEMPLATE_PARAMETERS_NUMBER_HPP
#define PSTADE_KETCHUP_CONFIG_LIMIT_TEMPLATE_PARAMETERS_NUMBER_HPP


// PStade.Ketchup
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/sub.hpp>


#if defined(PSTADE_KETCHUP_CFG_LIMIT_TEMPLATE_PARAMETERS_NUMBER)
    #define PSTADE_KETCHUP_CFG_NO_PREPROCESSED_HEADERS
    #define PSTADE_KETCHUP_LIMIT_ALT_MSG_MAP_SIZE \
        BOOST_PP_SUB(PSTADE_KETCHUP_CFG_LIMIT_TEMPLATE_PARAMETERS_NUMBER, 1)
    #define PSTADE_KETCHUP_LIMIT_BEGIN_MSG_MAP_SIZE \
        PSTADE_KETCHUP_CFG_LIMIT_TEMPLATE_PARAMETERS_NUMBER
    #define PSTADE_KETCHUP_LIMIT_IDSET_SIZE \
        PSTADE_KETCHUP_CFG_LIMIT_TEMPLATE_PARAMETERS_NUMBER
    #define PSTADE_KETCHUP_LIMIT_MESSAGE_PROCESSOR_BASE_SIZE \
        BOOST_PP_SUB(PSTADE_KETCHUP_CFG_LIMIT_TEMPLATE_PARAMETERS_NUMBER, 1)
#endif


#endif