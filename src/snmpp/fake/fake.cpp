// fake.cpp --- 
// 
// Filename: fake.cpp
// Author: Alexandre BIGUET
// Created: Mer sep 13 21:09:00 2017 (+0200)
// Last-Updated: Mer sep 13 21:09:35 2017 (+0200)
//           By: Alexandre BIGUET
//     Update #: 4
// 
// snmpp
// 

#include "fake.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>
namespace pt = boost::posix_time;

namespace snmpp { namespace fake {

double fake( double x ) {
    return x;
}


std::string getCurrentDate(){
    pt::ptime now = pt::second_clock::local_time();

    std::stringstream ss;
    ss<<now.date().year()
      <<"-"<<now.date().month()
      <<"-"<<now.date().day()
      <<"-"<<now.time_of_day().hours()
      <<"-"<<now.time_of_day().minutes()
      <<"-"<<now.time_of_day().seconds();

    return ss.str();
}

}} // namespace snmpp::fake

// 
// fake.cpp ends here
