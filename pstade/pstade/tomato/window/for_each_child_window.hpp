#ifndef PSTADE_TOMATO_WINDOW_FOR_EACH_CHILD_WINDOW_HPP
#define PSTADE_TOMATO_WINDOW_FOR_EACH_CHILD_WINDOW_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/addressof.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/function.hpp>
#include "./window_ptr.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace tomato {


namespace for_each_child_window_detail {


    template< class UnaryFun >
    BOOL CALLBACK proc(HWND hWnd, LPARAM lParam)
    {
        try {
            UnaryFun& yield = *reinterpret_cast<UnaryFun *>(lParam);
            window_ref wnd(hWnd);

            yield(wnd.handle());
            return TRUE;
        }
        catch (...) { // never propagate.
            return FALSE;
        }
    }


    template< class UnaryFun > inline
    void aux(window_ptr parent, UnaryFun yield)
    {
        // Note:
        // if no child, EnumChildWindows "fails"
        // and the GetLastError value is undocumented.
        // So there seems no way to know whether or not
        // api failed.
        ::EnumChildWindows(
            parent.get(),
            &proc<UnaryFun>,
            reinterpret_cast<LPARAM>(boost::addressof(yield))
        );
    }


    struct baby
    {
        // 'NULL' means the root window.
        explicit baby(window_ptr parent) :
            m_parent(parent)
        { }

        HWND parent() const
        {
            return m_parent.get();
        }

        typedef HWND routine_result_type;

        template< class Unused, class UnaryFun >
        struct result :
            egg::by_value<UnaryFun>
        { };

        template< class Result, class UnaryFun >
        Result call(UnaryFun& yield)
        {
            // Workaround:
            // VC++7.1/8 fails to decay function-reference.
            // Without the explicit parameter, 'UnaryFun' of 'aux<UnaryFun>(...)'
            // would be deduced as a *reference* type. Lovely!
            for_each_child_window_detail::aux<Result>(m_parent, yield);
            return yield;
        }

    private:
        window_ptr m_parent;
    };


} // namespace for_each_child_window_detail


typedef egg::function<for_each_child_window_detail::baby>
for_each_child_window;


} } // namespace pstade::tomato


#endif
