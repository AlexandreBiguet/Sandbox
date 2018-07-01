//
//  PartialInt.cpp 
//  snmpp
//
//  Created on 02/11/2017 at 22:25.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include <iostream>
#include <snmpp/Tensor/MultiIndex.hpp>

int main (){

    /**
     * The Integral type overload of the MultiIndex class allows for example
     * to simulate N nested for loops
     *
     * Let's consider we want to simulate 3 nested for loops.
     *
     * for (i = Ii ; i < Ni ; ++i)
     *    for (j = Ij ; j < Nj ; ++j)
     *       for(k = Ik ; k < Nk ; ++k)
     */


    const std::size_t Nfor(3); // 3 nested for loops

    const std::size_t Ni(5);
    const std::size_t Nj(3);
    const std::size_t Nk(6);

    const std::size_t Ii(3);
    const std::size_t Ij(2);
    const std::size_t Ik(4);

    std::vector<std::size_t> Nmax({Ni, Nj, Nk});
    std::vector<std::size_t> input({Ii, Ij, Ik});

    snmpp::tensor::MultiIndex<std::size_t> index(Nmax, input);

    while (index.next()) {

        for(std::size_t i = 0 ; i < Nfor ; ++i) {
            std::cout << index.get(i) << "  ";
        }

        std::cout<<'\n';
    }


    return 0;
}


// PartialInt.cpp ends here