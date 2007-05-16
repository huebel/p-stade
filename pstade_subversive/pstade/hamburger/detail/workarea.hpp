#ifndef PSTADE_HAMBURGER_DETAIL_WORKAREA_HPP
#define PSTADE_HAMBURGER_DETAIL_WORKAREA_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/tomato/boolean_cast.hpp>
#include "../point.hpp"
#include "../rectangle.hpp"


namespace pstade { namespace hamburger { namespace detail {


    // Todo: multi-monitor
    //
    inline
    bool is_in_workarea(point const& pt)
    {
        rectangle rc;
        if (!::SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0))
            return true;

        return rc.PtInRect(pt)|tomato::to_boolean;
    }


    inline
    bool is_cross_workarea(rectangle const& rc)
    {
        rectangle w;
        if (!::SystemParametersInfo(SPI_GETWORKAREA, 0, &w, 0))
            return true;

        return !(rc & w).IsRectEmpty()|tomato::to_boolean;
    }


} } } // namespace pstade::hamburger::detail


#endif
