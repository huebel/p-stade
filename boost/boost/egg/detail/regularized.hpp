#ifndef BOOST_EGG_DETAIL_REGULARIZED_HPP
#define BOOST_EGG_DETAIL_REGULARIZED_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Adds Assignable and DefaultConstructible
// facility to a CopyConstructible type 'X'.


#include <boost/assert.hpp>
#include <boost/operators.hpp> // totally_ordered
#include <boost/optional/optional.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/egg/do_swap.hpp>
#include <boost/egg/detail/bool_testable.hpp>
#include <boost/egg/detail/swappable.hpp>


namespace boost { namespace egg { namespace details {


    template<class X>
    struct dummy_assignable
    {
    private:
        typedef dummy_assignable self_t;

    public:
        X m_x;

        explicit dummy_assignable(X const &x) :
            m_x(x)
        { }

        // never called if uninitialized
        self_t &operator=(self_t const &)
        {
            BOOST_ASSERT(false);
            return *this;
        }
    };


    template<class X>
    struct regularized :
        bool_testable   < regularized<X>,
        swappable       < regularized<X>,
        totally_ordered1< regularized<X> > > >
    {
    private:
        typedef regularized self_t;
        typedef dummy_assignable<X> dummy_assignable_t;

    public:
    // structors
        explicit regularized()
        { }

        explicit regularized(X const &x) :
            m_opx(dummy_assignable_t(x))
        { }

    // assignments
        self_t &operator=(self_t const &other)
        {
            m_opx.reset(); // Force uninitialized.
            m_opx = other.m_opx;
            return *this;
        }

    // dereference
        X &operator *()
        {
            return (*m_opx).m_x;
        }

        X const &operator *() const
        {
            return (*m_opx).m_x;
        }

    // bool_testable
        operator safe_bool() const
        {
            return make_safe_bool(m_opx);
        }

    // swappable
        void swap(self_t &other)
        {
            egg::do_swap(m_opx, other.m_opx);
        }

    // totally_ordered
        bool operator< (self_t const &other) const
        {
            return m_opx < other.m_opx;
        }

        bool operator==(self_t const &other) const
        {
            return m_opx == other.m_opx;
        }

    private:
        optional<dummy_assignable_t> m_opx;
    };


} } } // namespace boost::egg::details


// dereference extension
//

#include <boost/egg/bll/extension_fwd.hpp>


namespace boost { namespace lambda {


    template<class X>
    struct return_type_1< other_action<contentsof_action>, egg::details::regularized<X> >
    {
        typedef X &type;
    };

    template<class X>
    struct return_type_1< other_action<contentsof_action>, egg::details::regularized<X> const >
    {
        typedef X const &type;
    };


} } // namespace boost::lambda


#endif
