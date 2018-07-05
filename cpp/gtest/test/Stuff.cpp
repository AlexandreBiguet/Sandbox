/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   05 - Jul - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 05 - Jul - 2018
 */

#include <myTest/Stuff.hpp>

#include <iostream>

#include <gtest/gtest.h>

TEST(myTestStuff, hello) { ASSERT_NO_THROW(myTest::hello("Bryan")); }

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
