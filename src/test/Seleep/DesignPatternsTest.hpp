#ifndef DesignPatternsTest_hpp
#define DesignPatternsTest_hpp

#include "oatpp-test/UnitTest.hpp"

class DesignPatternsTest : public oatpp::test::UnitTest {
 public:
  DesignPatternsTest() : UnitTest("TEST[DesignPatternsTestSeleep]") {}
  void onRun() override;
};

#endif  // DesignPatternsTest_hpp
