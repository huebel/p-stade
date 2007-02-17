#ifndef PSTADE_OVEN_ANY_ITERATOR_HPP
#define PSTADE_OVEN_ANY_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Waiting for Thomas Becker's implementation to come into the Boost...
// http://thbecker.net/free_software_utilities/type_erasure_for_cpp_iterators/start_page.html


#include <cstddef> // ptrdiff_t
#include <boost/assert.hpp>
#include <boost/cast.hpp> // polymorphic_downcast
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/clone_ptr.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/use_default.hpp>
#include "./detail/reference_is_convertible.hpp"


namespace pstade { namespace oven {


template<
    class Reference,
    class Traversal,
    class Value,
    class Difference
>
struct any_iterator;


namespace any_iterator_detail {


    template< class To, class From > inline
    To const& downcast(From const& from)
    {
        // 'Iterator_' types must be the same.
        return *boost::polymorphic_downcast<To const *>(&from);
    }


    template< class Reference, class Traversal, class Difference, class Traversal_ = Traversal >
    struct placeholder :
        private boost::noncopyable
    {
        typedef placeholder<Reference, Traversal_, Difference> most_derived_t;

        virtual ~placeholder() { }
        virtual most_derived_t *clone() const = 0;

        virtual Reference dereference() const = 0;
        virtual bool equal(most_derived_t const& other) const = 0;
        virtual void increment() = 0;
    };

    template< class Reference, class Difference, class Traversal_ >
    struct placeholder<Reference, boost::bidirectional_traversal_tag, Difference, Traversal_> :
        placeholder<Reference, boost::forward_traversal_tag, Difference, Traversal_>
    {
        virtual void decrement() = 0;
    };

    template< class Reference, class Difference, class Traversal_ >
    struct placeholder<Reference, boost::random_access_traversal_tag, Difference, Traversal_> :
        placeholder<Reference, boost::bidirectional_traversal_tag, Difference, Traversal_>
    {
        virtual void advance(Difference const& d) = 0;
        virtual Difference difference_to(placeholder const& other) const = 0;
    };


    // Clonable concept
    template< class Reference, class Traversal, class Difference > inline
    placeholder<Reference, Traversal, Difference> *
    new_clone(placeholder<Reference, Traversal, Difference> const& ph)
    {
        return ph.clone();
    }


    template< class Iterator, class Traversal, class Difference >
    struct difference_is_convertible :
        boost::mpl::eval_if< boost::is_same<Traversal, boost::random_access_traversal_tag>,
            boost::is_convertible<typename boost::iterator_difference<Iterator>::type, Difference>,
            boost::mpl::true_
        >
    { };


    template< class Iterator, class Reference, class Traversal, class Difference >
    struct holder :
        placeholder<Reference, Traversal, Difference>
    {
    private:
        BOOST_MPL_ASSERT((detail::reference_is_convertible_aux<typename boost::iterator_reference<Iterator>::type, Reference>));
        BOOST_MPL_ASSERT((boost::is_convertible<typename boost::iterator_traversal<Iterator>::type, Traversal>));
        BOOST_MPL_ASSERT((difference_is_convertible<Iterator, Traversal, Difference>));

        typedef holder self_t;
        typedef placeholder<Reference, Traversal, Difference> placeholder_t;

    public:
        explicit holder(Iterator const& held) :
          m_held(held)
        { }

        Iterator const& held() const
        {
            return m_held;
        }

    private:
        Iterator m_held;

        placeholder_t *clone() const
        {
            return new self_t(m_held);
        }

    public:
        // It depends on the 'placeholder' whether or not these are 'virtual'.

        Reference dereference() const
        {
            return *m_held;
        }

        bool equal(placeholder_t const& other) const
        {
            return m_held == any_iterator_detail::downcast<self_t>(other).m_held;
        }

        void increment()
        {
            ++m_held;
        }

        void decrement()
        {
            --m_held;
        }

        void advance(Difference const& d)
        {
            m_held += d;
        }

        Difference difference_to(placeholder_t const& other) const
        {
            return any_iterator_detail::downcast<self_t>(other).m_held - m_held;
        }
    };


    template<
        class Reference,
        class Traversal,
        class Value,
        class Difference
    >
    struct super_
    {
        typedef typename
            use_default_eval_to< Value, remove_cvr<Reference> >::type
        value_t;

        typedef typename
            use_default_to<Difference, std::ptrdiff_t>::type
        diff_t;

        typedef
            boost::iterator_facade<
                any_iterator<Reference, Traversal, Value, Difference>,
                value_t,
                Traversal,
                Reference,
                diff_t
            >
        type;
    };


    // As a recursive range is Forward, 'shared_ptr' isn't used.
    // Hence there is no reference cycles.
    template< class Traversal, class PlaceHolder >
    struct pimpl_of :
        boost::mpl::if_< boost::is_same<Traversal, boost::single_pass_traversal_tag>,
            boost::shared_ptr<PlaceHolder>,
            clone_ptr<PlaceHolder>
        >
    { };


} // namespace any_iterator_detail


template<
    class Reference,
    class Traversal,
    class Value      = boost::use_default,
    class Difference = boost::use_default
>
struct any_iterator :
    any_iterator_detail::super_<Reference, Traversal, Value, Difference>::type
{
private:
    typedef typename any_iterator_detail::super_<Reference, Traversal, Value, Difference>::type super_t;
    typedef typename super_t::difference_type diff_t;
    typedef any_iterator_detail::placeholder<Reference, Traversal, diff_t> placeholder_t;
    typedef typename any_iterator_detail::pimpl_of<Traversal, placeholder_t>::type pimpl_t;

public:
    explicit any_iterator()
    { }

    // There is no implicit constructor.
    // The implementation by Thomas Becker tells why.

    template< class Iterator_ >
    explicit any_iterator(Iterator_ const& it) :
        m_pimpl(new
            any_iterator_detail::holder<Iterator_, Reference, Traversal, diff_t>
        (it))
    { }

    template< class Iterator_ >
    Iterator_ const& base() const
    {
        return any_iterator_detail::downcast<
            any_iterator_detail::holder<Iterator_, Reference, Traversal, diff_t>
        >(*m_pimpl).held();
    }

private:
    pimpl_t m_pimpl;

friend class boost::iterator_core_access;
    Reference dereference() const
    {
        return m_pimpl->dereference();
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        return m_pimpl->equal(*other.m_pimpl);
    }

    void increment()
    {
        m_pimpl->increment();
    }

    void decrement()
    {
        m_pimpl->decrement();
    }

    void advance(diff_t const& d)
    {
        m_pimpl->advance(d);
    }

    template< class Other >
    diff_t distance_to(Other const& other) const
    {
        return m_pimpl->difference_to(*other.m_pimpl);
    }
};


} } // namespace pstade::oven


#endif
