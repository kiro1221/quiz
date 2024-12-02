#ifndef DoxygenTest_hpp
#define DoxygenTest_hpp

#include "oatpp-test/UnitTest.hpp"

class DoxygenTest : public oatpp::test::UnitTest {
 public:
  DoxygenTest() : UnitTest("TEST[DoxygenTestSeleep]") {}
  void onRun() override;
};

#endif  // DoxygenTest_hpp

