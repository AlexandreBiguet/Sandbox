/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   24 - Jun - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 24 - Jun - 2018
 */

#include <myTest/Cool.hpp>

#include <iostream>

#include <gtest/gtest.h>

TEST(myTestCool, getString) {
  ASSERT_EQ("Good", myTest::getString(0));
  ASSERT_EQ("Morning", myTest::getString(1));
  ASSERT_EQ("Vietnam", myTest::getString(2));
  ASSERT_EQ("Nothing", myTest::getString(-1));
  ASSERT_EQ("Nothing", myTest::getString(3));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
