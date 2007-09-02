#ifndef PSTADE_BISCUIT_PARSER_DYNAMIC_VALSET_HPP
#define PSTADE_BISCUIT_PARSER_DYNAMIC_VALSET_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/mpl/void.hpp>
#include "./valsetn.hpp"


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

    #if defined(PSTADE_BISCUIT_CFG_NO_PREPROCESSED_HEADERS)
        #include "../../detail/preprocessing/valset.hpp"
    #else
        #include "../../detail/preprocessed/valset.hpp"
    #endif

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION


#endif