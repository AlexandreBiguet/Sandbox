#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <mocking/coin_flipper.hpp>
#include <mocking/rng.hpp>

namespace mocking {

class MockRng : public Rng {
 public:
  MOCK_CONST_METHOD2(generate, double(double, double));
};

}  // namespace mocking

TEST(CoinFlipper, ShouldReturnHeadsIfRandValueIsLessThanProbability) {
  // 1) Create mock objects (collaborators)
  mocking::MockRng rng;

  // 2) Specify your expectations of them
  EXPECT_CALL(rng, generate(testing::DoubleEq(0.0), testing::DoubleEq(1.0)))
      .Times(testing::Exactly(1))
      .WillOnce(testing::Return(0.25));

  // 3) Construct object(s) under test, passing mocks
  mocking::CoinFlipper coinFlipper(&rng);

  // 4) Run code under test
  mocking::CoinFlipper::Result result = coinFlipper.flip();

  // 5) Check output (using Google Test or some other framework)
  EXPECT_EQ(mocking::CoinFlipper::Result::Head, result);

  // 6) Let gmock automatically check mock expectations were met at end of test
}

TEST(CoinFlipper2, ShouldReturnHeadsIfRandValueIsLessThanProbability) {
  // 1) Create mock objects (collaborators)
  auto rng = std::make_shared<mocking::MockRng>();

  // 2) Specify your expectations of them
  EXPECT_CALL(*rng, generate(testing::DoubleEq(0.0), testing::DoubleEq(1.0)))
      .Times(testing::Exactly(1))
      .WillOnce(testing::Return(0.25));

  // 3) Construct object(s) under test, passing mocks
  mocking::CoinFlipper2 coinFlipper(rng);

  // 4) Run code under test
  mocking::CoinFlipper2::Result result = coinFlipper.flip();

  // 5) Check output (using Google Test or some other framework)
  EXPECT_EQ(mocking::CoinFlipper2::Result::Head, result);

  // 6) Let gmock automatically check mock expectations were met at end of test
}

class CoinFlipperFixture
    : public ::testing::TestWithParam<
          std::pair<double, mocking::CoinFlipper::Result> > {};

TEST_P(CoinFlipperFixture, CoinFlip) {
  const double randomVal = GetParam().first;
  const mocking::CoinFlipper::Result expectedResult = GetParam().second;

  mocking::MockRng rng;
  EXPECT_CALL(rng, generate(testing::DoubleEq(0.0), testing::DoubleEq(1.0)))
      .Times(testing::Exactly(1))
      .WillOnce(testing::Return(randomVal));

  mocking::CoinFlipper coinFlipper(&rng);
  mocking::CoinFlipper::Result result = coinFlipper.flip();

  EXPECT_EQ(expectedResult, result);
}

INSTANTIATE_TEST_SUITE_P(
    ValidRandomNumberGenerated, CoinFlipperFixture,
    testing::Values(std::make_pair(0.0, mocking::CoinFlipper::Result::Head),
                    std::make_pair(0.25, mocking::CoinFlipper::Result::Head),
                    std::make_pair(0.49999, mocking::CoinFlipper::Result::Head),
                    std::make_pair(0.5, mocking::CoinFlipper::Result::Tail),
                    std::make_pair(0.75, mocking::CoinFlipper::Result::Tail),
                    std::make_pair(1.0, mocking::CoinFlipper::Result::Tail)));

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
