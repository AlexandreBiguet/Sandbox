//
//  FormattedOutputSample.cpp 
//  snmpp
//
//  Created on 21/10/2017 at 17:48.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include <iostream>
#include <snmpp/Utils/FormattedOutput.hpp>

int main (){

    double v = 5.0;
    double y = -15.0;
    int n = 10;

    std::cout<<"without formatted format : \n";
    std::cout<<n<<" "<<v<<"\n"<<v<<" "<<n<<"\n";

    std::cout<<"with formatted format : \n";

    snmpp::utils::FormattedOutput c;

    std::cout<<c<<n<<c<<v<<c<<v<<c<<y<<"\n";
    std::cout<<c<<v<<c<<y<<c<<n<<c<<n<<std::endl;


    return 0;
}

// FormattedOutputSample.cpp ends here