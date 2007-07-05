#ifndef PSTADE_GRAVY_SET_MENU_DEFAULT_ITEM_HPP
#define PSTADE_GRAVY_SET_MENU_DEFAULT_ITEM_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/constant.hpp>
#include <pstade/copy_construct.hpp>
#include <pstade/unused.hpp>
#include "./boolean_cast.hpp"
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    struct op_set_menu_default_item
    {
        typedef bool result_type;

        bool operator()(menu_ref menu,
            UINT uItem = static_cast<UINT>(-1),  bool by_position = false) const
        {
#if !defined(_WIN32_WCE)
            return ::SetMenuDefaultItem(menu, uItem, pstade::copy_construct<UINT>(by_position))|to_boolean;
#else
            pstade::unused(menu, uItem, by_position);
            return true;
#endif // !defined(_WIN32_WCE)
        }
    };


    PSTADE_CONSTANT(set_menu_default_item, (op_set_menu_default_item))


} } // namespace pstade::gravy


#endif