#ifndef PSTADE_OVEN_JOINT_ITERATOR_HPP
#define PSTADE_OVEN_JOINT_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)




namespace pstade { namespace oven {





PSTADE_OBJECT_GENERATOR(make_joint_iterator,
    (joint_iterator< deduce<_2, to_value>, deduce<_3, to_value> >) const)


} } // namespace pstade::oven


#endif
