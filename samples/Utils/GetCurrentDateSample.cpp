//
//  main.cpp.cpp 
//  snmpp
//
//  Created on 15/10/2017 at 22:29.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include <iostream>

#include <snmpp/Utils/Tools.hpp>

int main ( ){

    std::cout<<"Current date : "<<snmpp::utils::getCurrentDate()<<std::endl;

    return 0;
}

// main.cpp.cpp ends here