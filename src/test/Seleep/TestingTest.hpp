#ifndef TestingTest_hpp
#define TestingTest_hpp

#include "oatpp-test/UnitTest.hpp"

class TestingTest : public oatpp::test::UnitTest {
 public:
  TestingTest() : UnitTest("TEST[TestingTestSeleep]") {}
  void onRun() override;
};

#endif  // TestingTest_hpp

