#ifndef PSTADE_EGG_DEDUCE_HPP
#define PSTADE_EGG_DEDUCE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/pass_by.hpp>


namespace pstade { namespace egg {


    struct generator_error_argument_required;


    template<
        class A, class Deducer,
        class Default = generator_error_argument_required
    >
    struct deduce :
        boost::mpl::eval_if< boost::is_same<A, void>,
            boost::mpl::identity<Default>,
            boost::mpl::apply1<Deducer, A>
        >
    { };


    struct as_value
    {
        template<class A>
        struct apply :
            pass_by_value<A>
        { };
    };

    struct as_reference
    {
        template<class A>
        struct apply :
            boost::add_reference<A>
        { };
    };

    struct as_qualified
    {
        template<class A>
        struct apply :
            boost::mpl::identity<A>
        { };
    };


} } // namespace pstade::egg


#endif