//
//  VariablesTests.cpp 
//  snmpp
//
//  Created on 21/10/2017 at 11:34.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include <iostream>
#include <snmpp/Math/Core/Variables.hpp>

using namespace snmpp::math;

template <typename Key, typename ValueType>
void outputVar ( const core::Variables<Key, ValueType> &vars)
{
    for( const auto &it : vars ){
        std::string s( it.second.toString() );
        std::cout<<it.first<<" = "<<s<<std::endl;
    }
}

void testConstruction();
void testAdd();
void testCapacity();
void testEraseAndFind();
void testContainerStuff();
void testGetVariable();
void testConstructionFromMap();
void testGetType();
void testSet();
void testSizeType();
void testSetFromVariables();
void testSetFromMap();
void testGetKeys();

int main () {

// Already tested
// --------------------
//    testConstruction();
//    testAdd();
//    testCapacity();
//    testEraseAndFind();
//    testContainerStuff();
//    testGetVariable();
//    testConstructionFromMap();
//    testGetType();
//    testSet();
//    testSizeType();
//    testSetFromVariables();
//    testSetFromMap();
    testGetKeys();

    std::cout<<"Done \n";
    return 0;
}

/*
 * Implementation of test functions
 * Lot of code duplication but ....
 */

void testConstruction() {

    std::vector<std::tuple<std::string,double, VariableType>>
        m ({std::make_tuple("x", 1.0, VariableType::Running),
            std::make_tuple("y", 2.0, VariableType::Fixed)});
    core::Variables<std::string,double> Var(m);

    std::cout<<" 1) x and y values : \n";
    outputVar(Var);

    try {
        std::vector<std::tuple<std::string, double, VariableType>>
            m({std::make_tuple("x", 1.0, VariableType::Running),
               std::make_tuple("x", 2.0, VariableType::Fixed)});
        core::Variables<std::string, double> test(m);
    } catch (const std::exception &e) {
        std::cout << "This should throw : " << e.what() << std::endl;
    }

}


void testAdd() {

    std::vector<std::tuple<std::string,double, VariableType>>
        m ({std::make_tuple("x", 1.0, VariableType::Running),
            std::make_tuple("y", 2.0, VariableType::Fixed)});
    core::Variables<std::string,double> Var(m);

    Var.add( "z", core::Variable<double>(3.0, VariableType::Fixed));
    std::cout<<"\n 2) adding z value : \n";
    outputVar(Var);

    try {
        Var.add( "z", core::Variable<double>(3.0, VariableType::Fixed));
    } catch (const std::exception &e){
        std::cout<<"This should throw : "<<e.what()<<std::endl;
    }
}

void testCapacity() {

    std::vector<std::tuple<std::string,double, VariableType>>
        m ({std::make_tuple("x", 1.0, VariableType::Running),
            std::make_tuple("y", 2.0, VariableType::Fixed)});
    core::Variables<std::string,double> Var(m);

    if ( Var.empty() ){
        std::cout<<" empty() method returned true but should be false \n";
        throw std::logic_error(" empty() method : problem");
    }

    Var.clear();

    if ( !Var.empty() ){
        std::cout<<" clear() method was called but empty() returned false \n";
        throw std::logic_error(" clear() method : problem");
    }

    Var.add( "a", core::Variable<double>(3.0, VariableType::Running) );
    Var.add( "b", core::Variable<double>(2.0, VariableType::Running) );
    Var.add( "c", core::Variable<double>(1.0, VariableType::Running) );

    if( Var.size() != 3 ){
        std::cout<<" size() should returned 3 but returned "
                 <<Var.size() <<std::endl;
        throw std::logic_error("I did something wrong with size()");
    }

    outputVar(Var);
}

void testEraseAndFind() {

    core::Variables<std::string,double> Var;
    Var.add( "a", core::Variable<double>(3.0, VariableType::Running) );
    Var.add( "b", core::Variable<double>(2.0, VariableType::Running) );
    Var.add( "c", core::Variable<double>(1.0, VariableType::Running) );

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
}

void testContainerStuff() {

    core::Variables<std::string,double> Var;

    Var.add("tata", core::Variable<double>(1.0, VariableType::Fixed));
    Var.add("toto", core::Variable<double>(2.0, VariableType::Fixed));
    Var.add("prou", core::Variable<double>(2.0, VariableType::Fixed));

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
}

void testGetVariable() {

    core::Variables<std::string,double> Var;

    Var.add("tata", core::Variable<double>(1.0, VariableType::Fixed));
    Var.add("toto", core::Variable<double>(2.0, VariableType::Fixed));
    Var.add("prou", core::Variable<double>(2.0, VariableType::Fixed));

    try {
        Var.get("a");
    } catch ( const std::exception& e ){
        std::cout<<"This should throw";
    }

    auto vv = Var.get("toto");
    std::cout<<"\nget(toto) = "<<vv.toString()<<'\n';
}

void testConstructionFromMap() {

    core::Variables<std::string,double> Var;

    Var.add("tata", core::Variable<double>(1.0, VariableType::Fixed));
    Var.add("toto", core::Variable<double>(2.0, VariableType::Fixed));
    Var.add("prou", core::Variable<double>(2.0, VariableType::Fixed));

    auto map = Var.get();
    std::cout<<"\nGetting the map \n";
    for( const auto &it : map ){
        std::string s( it.second.toString() );
        std::cout<<it.first<<" = "<<s<<std::endl;
    }

    std::cout<<"\nConstructing from map : \n";

    core::Variables<std::string, double> Var2(map);

    outputVar(Var2);
}

void testGetType() {

    core::Variables<std::string,double> Var2;
    Var2.add( "x", core::Variable<double>(10.0, VariableType::Running));
    Var2.add( "y", core::Variable<double>(11.0, VariableType::Running));
    Var2.add( "z", core::Variable<double>(12.0, VariableType::Running));

    Var2.add( "a", core::Variable<double>(1.0, VariableType::Parameter));
    Var2.add( "b", core::Variable<double>(2.0, VariableType::Parameter));
    Var2.add( "c", core::Variable<double>(3.0, VariableType::Parameter));

    Var2.add( "x1", core::Variable<double>(-1.0, VariableType::Fixed));
    Var2.add( "x2", core::Variable<double>(-2.0, VariableType::Fixed));
    Var2.add( "x3", core::Variable<double>(-3.0, VariableType::Fixed));

    auto vrun = Var2.get(VariableType::Running);
    std::cout<<"\nList running variables : should be x, y, z \n";
    for(const auto &i: vrun ){
        std::cout<<i->first<<"("<<i->second.getValue()<<"), ";
    }
    std::cout<<std::endl;

    auto vfixed = Var2.get(VariableType::Fixed);
    std::cout<<"\nList fixed variables : should be x1, x2, x3 \n";
    for(const auto &i: vfixed ){
        std::cout<<i->first<<"("<<i->second.getValue()<<"), ";
    }
    std::cout<<std::endl;

    auto vparam = Var2.get(VariableType::Parameter);
    std::cout<<"\nList parameter variables : should be a, b, c \n";
    for(const auto &i: vparam ){
        std::cout<<i->first<<"("<<i->second.getValue()<<"), ";
    }
    std::cout<<std::endl;
}

void testSet() {

    core::Variables<std::string,double> Var2;

    Var2.add( "x", core::Variable<double>(10.0, VariableType::Running));
    Var2.add( "y", core::Variable<double>(11.0, VariableType::Running));
    Var2.add( "z", core::Variable<double>(12.0, VariableType::Running));

    Var2.add( "a", core::Variable<double>(1.0, VariableType::Parameter));
    Var2.add( "b", core::Variable<double>(2.0, VariableType::Parameter));
    Var2.add( "c", core::Variable<double>(3.0, VariableType::Parameter));

    Var2.add( "x1", core::Variable<double>(-1.0, VariableType::Fixed));
    Var2.add( "x2", core::Variable<double>(-2.0, VariableType::Fixed));
    Var2.add( "x3", core::Variable<double>(-3.0, VariableType::Fixed));

    Var2.set( "x", 100.0 );
    auto vcpy = Var2.get("x");
    std::cout<<"\nAfter setting 'x' to 100 we get : "
             <<vcpy.toString()<<std::endl;

    std::vector<std::pair<std::string,double>> vec;
    vec.push_back(std::make_pair("x", -2.0));
    vec.push_back(std::make_pair("y", -20.0));
    Var2.set( vec );
    std::cout<<"\nSet variables from vec of pair \n";
    std::cout<<"output should be : x = -2. and y = -20.0 \n";
    auto vrun = Var2.get(VariableType::Running);
    for(const auto &i: vrun ){
        std::cout<<i->first<<"("<<i->second.getValue()<<"), ";
    }
    std::cout<<std::endl;

    Var2.set( {std::make_pair("x1", 12.0), std::make_pair("x3", 15.0)} );
    std::cout<<"\nSet variables from vec of pair \n";
    std::cout<<"output should be x1 = 12.0 and x3 = 15.0 \n";
    auto vfixed = Var2.get(VariableType::Fixed);
    for(const auto &i: vfixed ){
        std::cout<<i->first<<"("<<i->second.getValue()<<"), ";
    }
    std::cout<<std::endl;
}

void testSizeType() {

    core::Variables<std::string,double> Var2;

    Var2.add( "x", core::Variable<double>(10.0, VariableType::Running));
    Var2.add( "a", core::Variable<double>(1.0, VariableType::Parameter));
    Var2.add( "x1", core::Variable<double>(-1.0, VariableType::Fixed));

    std::cout<<"Nb of running variable should be 1 and is "
             <<Var2.size(VariableType::Running)<<std::endl;

    std::cout<<"Nb of parameter variable should be 1 and is "
             <<Var2.size(VariableType::Parameter)<<std::endl;

    std::cout<<"Nb of fixed variable should be 1 and is "
             <<Var2.size(VariableType::Fixed)<<std::endl;
}

void testSetFromVariables() {

    core::Variables<std::string,double> Var2;

    Var2.add( "x", core::Variable<double>(10.0, VariableType::Running));
    Var2.add( "a", core::Variable<double>(1.0, VariableType::Parameter));
    Var2.add( "x1", core::Variable<double>(-1.0, VariableType::Fixed));

    core::Variables<std::string,double> Var;

    Var.add( "toto", core::Variable<double>(10.0, VariableType::Running));

    std::cout<<"\nsetting from another core::Variables<K,V> object \n";
    try {
        Var2.setFromVariables(Var);
    } catch(const std::exception &e){
        std::cout<<"This should throw a 'non-existing key' exception: "
                 <<e.what() <<std::endl;
    }

    try{
        core::Variables<std::string,double> VarTest(Var2);
        auto it = VarTest.find("x");
        it->second.setType(VariableType::Parameter);
        VarTest.setFromVariables(Var2);
    } catch (const std::exception &e){
        std::cout<<"this should throw a 'different type' exception :"
                 <<e.what()<<std::endl;
    }

    Var.clear();
    Var.add("x", core::Variable<double>(5.0, VariableType::Running));
    Var2.setFromVariables(Var);
    std::cout<<"\nNew value of 'x' should be 5 \n";
    outputVar(Var2);
}

void testSetFromMap() {

    core::Variables<std::string,double> Var2;
    Var2.add( "x", core::Variable<double>(10.0, VariableType::Running));
    Var2.add( "a", core::Variable<double>(1.0, VariableType::Parameter));

    try {
        Var2.setFromMap({{"x", 12.0}, {"y", 5.0}});
    } catch (const std::exception &e){
        std::cout<<"this should throw a 'non-existing key' exception :"
                 <<e.what()<<std::endl;
    }

    Var2.setFromMap({{"x", 12.0}, {"a", 5.0}});
    std::cout<<"\n New value of 'x' should be 12 and new value of 'a' should "
        "be 5 \n";
    outputVar(Var2);
}

void testGetKeys() {

    core::Variables<std::string,double> Var2;
    Var2.add( "x", core::Variable<double>(10.0, VariableType::Running));
    Var2.add( "y", core::Variable<double>(5.0, VariableType::Running));
    Var2.add( "a", core::Variable<double>(1.0, VariableType::Parameter));

    auto keys = Var2.getKeys(VariableType::Running);

    std::map<std::string, double > runmap;

    std::cout<<"List of keys of runnign type : (should be x, y) :\n";

    for( auto &i: keys ){
        std::cout<<i<<", ";
        runmap[i] = -1.0;
    }
    std::cout<<std::endl<<"Values of x and y should be -1.0 : \n";
    Var2.setFromMap(runmap);
    outputVar(Var2);
}


// VariablesTests.cpp ends here