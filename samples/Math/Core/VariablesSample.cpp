//
//  VariablesSample.cpp 
//  snmpp
//
//  Created on 17/10/2017 at 23:16.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include <iostream>

#include <snmpp/Math/Core/Variables.hpp>

using snmpp::math::VariableType ;

template <typename Key, typename ValueType>
void outputVar ( const snmpp::math::Variables<Key, ValueType> &vars)
{
    for( const auto &it : vars ){
        std::string s( it.second.toString() );
        std::cout<<it.first<<" = "<<s<<std::endl;
    }
}

int main () {

    std::vector<std::tuple<std::string,double, VariableType>>
                m ({std::make_tuple("x", 1.0, VariableType::Running),
                    std::make_tuple("y", 2.0, VariableType::Fixed)});
    snmpp::math::Variables<std::string,double> Var(m);

    std::cout<<" 1) x and y values : \n";
    outputVar(Var);

    try {
        std::vector<std::tuple<std::string,double, VariableType>>
            m ({std::make_tuple("x", 1.0, VariableType::Running),
                std::make_tuple("x", 2.0, VariableType::Fixed)});
        snmpp::math::Variables<std::string,double> Var(m);
    }catch (const std::exception &e ){
        std::cout<<"This should throw : "<<e.what()<<std::endl;
    }

    Var.add( "z", snmpp::math::Variable<double>(3.0, VariableType::Fixed));
    std::cout<<"\n 2) adding z value : \n";
    outputVar(Var);

    try {
        Var.add( "z", snmpp::math::Variable<double>(3.0, VariableType::Fixed));
    } catch (const std::exception &e){
        std::cout<<"This should throw : "<<e.what()<<std::endl;
    }

    if ( Var.empty() ){
        std::cout<<" empty() method returned true but should be false \n";
        throw std::logic_error(" empty() method : problem");
    }

    Var.clear();

    if ( !Var.empty() ){
        std::cout<<" clear() method was called but empty() returned false \n";
        throw std::logic_error(" clear() method : problem");
    }

    Var.add( "a", snmpp::math::Variable<double>(3.0, VariableType::Running) );
    Var.add( "b", snmpp::math::Variable<double>(2.0, VariableType::Running) );
    Var.add( "c", snmpp::math::Variable<double>(1.0, VariableType::Running) );

    if( Var.size() != 3 ){
        std::cout<<" size() should returned 3 but returned "
                 <<Var.size() <<std::endl;
        throw std::logic_error("I did something wrong with size()");
    }

    outputVar(Var);

    std::size_t n = Var.erase("b");

    if( n != 1 ) {
        std::cout<<" Removed 'b' from Variables but number of erased element "
            "was not 1 ("<<n<<") \n";

        throw std::logic_error(" -> erase('key') method : problem");
    }

    auto iter = Var.find("a");

    if( iter == Var.end() ){
        std::cout<<" Finding 'a' failed but 'a' is in the Variables \n";
        throw std::logic_error(" -> find() method : problem");
    }

    iter = Var.erase(iter);

    if ( iter == Var.end() ){
        std::cout<<" Removed 'a' element using iter returned by find() "
            "method\n";

        throw std::logic_error(" -> erase(iter) method : problem");
    }

    std::cout<<"Last element should be 'c' \n";
    std::cout<<iter->first<<" = "<<iter->second.toString()<<std::endl;

    Var.erase(iter);

    Var.add("tata", snmpp::math::Variable<double>(1.0, VariableType::Fixed));
    Var.add("toto", snmpp::math::Variable<double>(2.0, VariableType::Fixed));
    Var.add("prou", snmpp::math::Variable<double>(2.0, VariableType::Fixed));

    for( auto it = Var.begin() ; it != Var.end() ; ++it ){
        std::cout<<it->first<<" = "<<it->second.toString()<<"\n";
    }

    std::cout<<'\n';

    for ( auto it = Var.cbegin() ; it != Var.cend(); ++it ){
        std::cout<<it->first<<" = "<<it->second.toString()<<"\n";
    }

    std::cout<<'\n';

    for( auto it = Var.rbegin() ; it != Var.rend(); ++it ){
        std::cout<<it->first<<" = "<<it->second.toString()<<"\n";
    }

    std::cout<<'\n';

    for( auto it = Var.crbegin(); it != Var.crend(); ++it ){
        std::cout<<it->first<<" = "<<it->second.toString()<<"\n";
    }


    try {
        Var.get("a");
    } catch ( const std::exception& e ){
        std::cout<<"This should throw";
    }

    auto vv = Var.get("toto");
    std::cout<<"\nget(toto) = "<<vv.toString()<<'\n';


    auto map = Var.get();
    std::cout<<"\nGetting the map \n";
    for( const auto &it : map ){
        std::string s( it.second.toString() );
        std::cout<<it.first<<" = "<<s<<std::endl;
    }

    std::cout<<"\nConstructing from map : \n";

    snmpp::math::Variables<std::string, double> Var2(map);

    outputVar(Var2);

    return 0;
}


// VariablesSample.cpp ends here