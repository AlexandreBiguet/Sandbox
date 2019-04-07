//
//  Sequence.hpp 
//  snmpp
//
//  Created on 22/10/2017 at 15:46.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#pragma once

/******************************************************************************
 * Description: 
 * ------------
 * Classes which are 'equivalent' to the c++14 std::index_sequence
 ******************************************************************************/

/******************************************************************************
 * Possible enhancements:
 * ----------------------
 * For the moment I choose C++11 standard for which index_sequence is not
 * implemented. I don't want to use 14 standard just for that feature. So in
 * snmpp/Utils we will implemented a corresponding tool.
 *
 * If c++ 14 is needed elsewhere, we will go to 14
 ******************************************************************************/

#include <cstddef>

namespace snmpp { namespace utils {

template <std::size_t ... >
struct Sequence {};

template <std::size_t N, std::size_t ...I>
struct SequenceGenerator : SequenceGenerator<N-1, N-1, I...>{};

template< std::size_t ...I>
struct SequenceGenerator<0, I...> {
    typedef Sequence<I...> type;
};


}} // namespace snmpp::utils

// Sequence.hpp ends here