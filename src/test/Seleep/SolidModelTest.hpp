#ifndef SolidModelTest_hpp
#define SolidModelTest_hpp

#include "oatpp-test/UnitTest.hpp"

class SolidModelTest : public oatpp::test::UnitTest {
 public:
  SolidModelTest() : oatpp::test::UnitTest("SolidModelTest") {}
  void onRun() override;
};

#endif /* SolidModelTest_hpp */
