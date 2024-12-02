#ifndef SeleepTest_hpp
#define SeleepTest_hpp

#include "oatpp-test/UnitTest.hpp"

class SeleepTest : public oatpp::test::UnitTest {
 public:
  SeleepTest() : UnitTest("TEST[Seleep]") {}
  void onRun() override;
};

#endif  // SeleepTest_hpp
