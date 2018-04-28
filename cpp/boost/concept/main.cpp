//
//  main.cpp 
//  Sandbox
//
//  Created by Alexandre Biguet on 28/04/2018 at 21:27.
//  Copyright © 2017 UAVIA. All rights reserved.
//  
//

#include <iostream>
#include <cmath>
#include <string>

#include <boost/concept/usage.hpp>
#include <boost/concept_check.hpp>

struct Hello {

  void operator() (const std::string& name) const {
    std::cout << "Hello, " << name << "\n";
  }

  static void speak(const std::string& name) {
    std::cout << "Hello, " << name << "\n";
  }

};

template <class T>
struct canSpeakStatic {
 public:
  BOOST_CONCEPT_USAGE(canSpeakStatic)
  {
    T::speak("John Doe");
  }
 private:
  T t; // must be data members
};

template < typename SpeakerType >
struct Louder {

  BOOST_CONCEPT_ASSERT((canSpeakStatic<SpeakerType>));

  Louder() = default;

  void speakHigh () const {
    _speaker("john");
  }

  SpeakerType _speaker;

};

struct Mute {
  double pi() const {
    return M_PI;
  }
};

int main ( ) {

  Louder<Hello> louder;
  louder.speakHigh();

  // The following fails at compilation as expected since
  // the Mute class does not have a static speak method

//  Louder<Mute> louder2;
//  louder2.speakHigh();

  return 0;
}


// main.cpp ends here