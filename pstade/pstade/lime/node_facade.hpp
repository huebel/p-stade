#ifndef PSTADE_LIME_NODE_FACADE_HPP
#define PSTADE_LIME_NODE_FACADE_HPP


// PStade.Lime
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <map>
#include <string>
#include <boost/foreach.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>
#include <pstade/if_debug.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/range_reference.hpp>
#include <pstade/overload.hpp>
#include <pstade/ustring.hpp>
#include <pstade/what.hpp>
#include "./error.hpp"
#include "./new_node.hpp"


namespace pstade { namespace lime {


struct node_not_found :
    error
{
    explicit node_not_found(std::string const& what) :
        error(what)
    { }
};


namespace node_facade_detail {


    inline
    void throw_error(ustring const& name)
    {
        node_not_found err(pstade::what("<node-not-found>", name));
        boost::throw_exception(err);
    }


    template< class Node >
    typename oven::range_reference<Node>::type
    get_child(Node& parent, ustring const& childName)
    {
        typedef typename oven::range_reference<Node>::type child_t;

        BOOST_FOREACH (child_t child, parent) {
            if (oven::equals(child.name(), childName))
                return child;
        }

        node_facade_detail::throw_error(childName);
        PSTADE_IF_DEBUG( throw 0; ) // suppress warning
    }


} // namesapce node_facade_detail


template< class Derived >
struct node_facade :
    boost::ptr_list<Derived>,
    private boost::noncopyable
{
private:
    typedef std::map<ustring, ustring> attributes_t;

public:
// structors
    explicit node_facade()
    { }

    explicit node_facade(ustring const& name) :
        m_name(name)
    { }

    explicit node_facade(Derived& parent, ustring const& name) :
        m_parent(parent), m_name(name)
    { }

    virtual ~node_facade()
    { }

// accessors
    boost::optional<Derived&> const& parent() const
    {
        return m_parent;
    }

    ustring const& name() const
    {
        return m_name;
    }

    attributes_t& attributes()
    {
        return m_atts;
    }

// operators, prefer 'friend injection' for strict parameter type.
    friend
    Derived& operator/(Derived& node, ustring const& childName)
    {
        return node_facade_detail::get_child(node, childName);
    }

    friend
    ustring& operator%(Derived& node, ustring const& attName)
    {
        return node.attributes()[attName];
    }

    friend
    Derived& operator+=(Derived& node, ustring const& childName)
    {
        node.push_back(lime::new_node(node, childName));
        return node;
    }

public:
    void detail_construct(Derived& parent, ustring const& name)
    {
        m_parent = parent;
        m_name = name;
    }

private:
    boost::optional<Derived&> m_parent;
    ustring m_name;
    attributes_t m_atts;
};


} } // namespace pstade::lime


#endif
