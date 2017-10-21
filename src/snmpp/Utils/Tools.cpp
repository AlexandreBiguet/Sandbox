//
//  Tools.cpp 
//  snmpp
//
//  Created on 21/10/2017 at 15:08.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include <boost/date_time/posix_time/posix_time.hpp>

namespace snmpp { namespace utils {

namespace pt = boost::posix_time;

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


}} // namespace snmpp::utils


// Tools.cpp ends here