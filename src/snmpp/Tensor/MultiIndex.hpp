//
//  MultiIndex.hpp 
//  snmpp
//
//  Created on 01/11/2017 at 21:42.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#pragma once

/* Structure permettant d'obtenir par suite d'appel à multi_index_next
   toutes les possibilités de dim indices chacun allant de 0 à
   Nmax[i]-1

   Cette stucture permet de simuler dim boucles for imbriquées les
   unes dans les autres.
*/

/******************************************************************************
 * Description: 
 * ------------
 * Let's consider a vector of type T of fixed size.
 * Each element of the vector is allowed to run from 'begin' to 'end'.
 *
 * The MultiIndex class allows to get every combination of possible values.
 *
 * For example:
 * Let v be a vector of integer type of fixed size dim
 * Each element of the vector can run from 0 to N_i - 1, where N_i is the
 * maximum value that the i-th element can reach
 * By successive call of the next() method we get :
 * ( 0, 0, ..., 0) -> (0, 0, ..., 1) -> ... -> ( 0, 1, ..., 0) -> (0, 1, ..., 1)
 * -> ... -> (1, 1, ..., 1) -> ... -> (N_0-1, N_1 -1, ..., N_[dim-1] - 1)
 *
 *
 * In the implementation, N is called _Nmax
 *
 ******************************************************************************/

/******************************************************************************
 * Possible enhancements:
 * ----------------------
 * See TODOs
 ******************************************************************************/

#include <vector>
#include <type_traits>

namespace snmpp { namespace tensor {

// typename std::enable_if<std::is_integral<T>::value>::type

/**
 * Specialization for integer template parameter
 * */
template < typename T >
class MultiIndex{

    /***************************************************************************
     * Interface
     **************************************************************************/

  public:

    /**
     * Constructor
     * @input is the initial value of each element
     * @Nmax is their maximum value they can take.
     * -> If T is an iterator-like object Nmax can be construted using
     * std::distance
     * */
    MultiIndex(const std::vector<std::size_t>& Nmax,
               const std::vector<T>&input )
        : _input(input),
          _data(input),
          _Nmax(Nmax),
          _Ntot(1),
          _dim(Nmax.size()),
          _Ncur(0)
    {

        // sizes of input and Nmax vectors must be equal
        if( _input.size() != _Nmax.size() ){
            throw std::logic_error("MultiIndex : Nmax and input vector must "
                                       "have equal size");
        }

        for( std::size_t i = 0 ; i < _dim; ++i ){
            _Ntot *= ( _Nmax[i] - _input[i]);
        }

    }


    /**
     * Constructor
     * This constructor must not be used if T is an iterator
     * TODO : disable this constructor for iterator types
     * */
    explicit MultiIndex( const std::vector<std::size_t> &Nmax )
        : MultiIndex(Nmax, std::vector<T>(Nmax.size(),0)) {
        
    }


    /**
     * Computes the next possible combination of indexes.
     * Returns true if other combinations can be computed.
     * Returns false if the last combination was computed
     * */
    bool next() {

        if ( _Ncur == _Ntot ){
            return false;
        }

        if ( _Ncur == 0 ){
            ++_Ncur;
            return true;
        }

        ++_data[_dim - 1];

        std::size_t i = 1;

        while ( _data[_dim - i] == _Nmax[ _dim - i ] ){

            _data  [ _dim - i     ]  = _input[ _dim - i ];
            ++_data[ _dim - i - 1 ];

            ++i;
        }

        ++_Ncur;
        return true;
    }

    /**
     * Returns a copy of the i-th element of the current combination
     * */
    T get( std::size_t i ) const {
        return _data[i];
    }

    /***************************************************************************
     * Private
     **************************************************************************/

  private:

    /**
     * This vector holds the input value of each element
     * */
    const std::vector<T> _input;

    /**
     * This vector holds the current value of each element of the vector
     * */
    std::vector<T> _data;

    /**
     * This vector holds the maximum value that each element can reach
     * */
    std::vector<std::size_t> _Nmax;

    /**
     * This is the number of possible combination of each value. It is
     * defined by the sum of all _Nmax[i] value
     * */
    std::size_t _Ntot;

    /**
     * Holds the (constant) size of the input Nmax vector
     * */
    std::size_t _dim;

    /**
     * Holds the current index (goes from 0 to _dim - 1)
     * */
    std::size_t _Ncur;

};




}} // namespace snmpp::tensor

// MultiIndex.hpp ends here