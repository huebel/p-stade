#ifndef PSTADE_EGG_DETAIL_LITTLE_OF_HPP
#define PSTADE_EGG_DETAIL_LITTLE_OF_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/remove_cv.hpp>
#include "../function_fwd.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Function>
    struct little_of_aux
    {
        typedef typename Function::little_type type;
    };

    // minimize name lookup.
    template<class Little, class Strategy>
    struct little_of_aux< function<Little, Strategy> >
    {
        typedef Little type;
    };


    template<class Function>
    struct little_of :
        little_of_aux<typename boost::remove_cv<Function>::type>
    { };


} } } // namespace pstade::egg::detail


#endif
