#pragma once

#include <boost/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/enum_params_with_defaults.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <pstade/crtp_cast.hpp>
#include "../config/limit_message_processor_base_size.hpp"
#include "./entry_subset.hpp"
#include "./process_window_message.hpp"

#include "../cmd_ui/detail/handler_entry_set_include.ipp"
#include "../crack/detail/handler_entry_set_declare.ipp"

///////////////////////////////////////////////////////////////////////////////
// Note:
//   message_processor is the ambiguity buster.
//
//   As entry_subset has only classes,
//   multiple inheritance makes no ambiguity:
//
//     struct A { struct X { }; };
//
//   A is just a namespace.
//
#pragma warning(push)
#pragma warning(disable: 4584) // base-class 'meta_unique_base<Base>' is already a base-class
//
//   But handler-entries are class templates,
//   so they makes ambiguity:
//
//     template< class T >
//     struct B { struct X { T x; }; };
//
//   B<int> and B<char> are different namespaces.
//
//   By the way, you need not care about access control
//   of entry_subset thanks to C++ Standard 11.7.
//

namespace pstade { namespace ketchup {


namespace message_processor_detail {

	// prepare for (Sequence == entry_subset)
	template< class Base >
	struct meta_unique_base : Base
	{
		typedef meta_unique_base type;
	};

	#define PSTADE_KETCHUP_DETAIL_MAKE_UNIQUE_BASE(z, n, unused) \
		struct BOOST_PP_CAT(unique_base, n) { }; \
	/**/

	BOOST_PP_REPEAT(PSTADE_KETCHUP_LIMIT_MESSAGE_PROCESSOR_BASE_SIZE, PSTADE_KETCHUP_DETAIL_MAKE_UNIQUE_BASE, ~)

} // namespace message_processor_detail


///////////////////////////////////////////////////////////////////////////////
// message_processor
//
template<
	class Derived,
	BOOST_PP_ENUM_PARAMS_WITH_DEFAULTS(PSTADE_KETCHUP_LIMIT_MESSAGE_PROCESSOR_BASE_SIZE, class BaseT, message_processor_detail::unique_base)
>
struct message_processor :
	message_processor_detail::meta_unique_base<entry_subset>::type,
	BOOST_PP_ENUM_PARAMS(PSTADE_KETCHUP_LIMIT_MESSAGE_PROCESSOR_BASE_SIZE, BaseT)
{
#if !defined(BOOST_NO_POINTER_TO_MEMBER_TEMPLATE_PARAMETERS)
	#include "../win/detail/handler_entry_set.ipp"
	#include "../crack/detail/handler_entry_set.ipp"
	#include "../cmd_ui/detail/handler_entry_set.ipp"
#endif

	typedef Derived _;

	BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg,
		WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0)
	{
		Derived& d = pstade::auto_derived(this);

		return ketchup::process_window_message(d, hWnd, uMsg,
			wParam, lParam, lResult, dwMsgMapID);
	}
};


} } // namespace pstade::ketchup

#pragma warning(pop)

#include "../crack/detail/handler_entry_set_undef.ipp"
