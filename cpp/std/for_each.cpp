//
//  for_each.cpp 
//  Sandbox
//
//  Created by Alexandre Biguet on 14/05/2018 at 15:27.
//  Copyright © 2017 . All rights reserved.
//  
//

/**
 * testing std::for_each
 */

#include <algorithm>
#include <iostream>
#include <vector>

struct Data {

  Data (double low, double high) : _low(low) , _high(high) { }

  double _low;
  double _high;
};

int main() {

  std::vector<Data> datae { {   5.0, 120.0},
                            {   2.0, 140.0},
                            {  15.0,  60.0},
                            { 100.0, 110.0}};

  double max_low  = std::numeric_limits<double>::min();
  double min_high = std::numeric_limits<double>::max();

  // Finding the maximum value of _low
  // Finding the minimum value of _high

  double exp_max_low  = 100.0;
  double exp_min_high =  60.0;

  std::for_each(datae.begin(), datae.end(),
                [&min_high, &max_low] (std::vector<Data>::const_reference& element){

    if (element._low > max_low) {
      max_low = element._low;
    }

    if (element._high < min_high) {
      min_high = element._high;
    }

  });

  std::cout << "Max Low \n";
  std::cout << "[expected : "<<exp_max_low<<"] [found:"<<max_low<<"] \n";

  std::cout << "Min high \n";
  std::cout << "[expected : "<<exp_min_high<<"] [found:"<<min_high<<"] \n";

  return 0;
}

// for_each.cpp ends here