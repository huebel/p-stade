#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./static_initialization.hpp"


T_my_id const &get_my_id1( )
{
   return my_id;
}

int i = get_my_id2().little().touch;


T_my_idr const &get_my_idr1( )
{
   return my_idr;
}

int ir = get_my_idr2().little().base().little().touch;


