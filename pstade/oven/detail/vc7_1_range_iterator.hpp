// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_RANGE_DETAIL_VC7_1_RANGE_ITERATOR_HPP
#define BOOST_RANGE_DETAIL_VC7_1_RANGE_ITERATOR_HPP


#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/mutable_iterator.hpp>


namespace boost {
    
    
    namespace range_detail_vc7_1 {


        template<class Sig, bool IsConst>
        struct range_iterator_aux;

        template<class Range>
        struct range_iterator_aux<void(Range), true>
            : range_const_iterator<Range>
        {};

        template<class Range>
        struct range_iterator_aux<void(Range), false>
            : range_mutable_iterator<Range>
        {};

        // Decayed form resurrects the type system.
        template<class T>
        struct range_iterator_aux<void(T[]), true>
        {
            typedef T const *type;
        };

        template<class T>
        struct range_iterator_aux<void(T[]), false>
        {
            typedef T *type;
        };


        template<class Range>
        struct range_iterator
            : range_iterator_aux<void(typename boost::remove_const<Range>::type), is_const<Range>::value>
        {};


    } // namespace range_detail_vc7_1


    template<class Range>
    struct vc7_1_range_iterator
        : range_detail_vc7_1::range_iterator<Range>
    {};


} // namespace boost


#endif
